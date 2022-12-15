#include "CharacterInstance.hpp"

#include "Dice.hpp"
#include "Item.hpp"
#include "Action.hpp"
#include "GameMap.hpp"

namespace DnD {
CharacterInstance::CharacterInstance(size_t id, Character& original, std::unique_ptr<Position>&& pos,
                                     GameMap& map, int money, const SharedStorage<Item>& items) :
        OnLocation(std::move(pos), map),
        items_(items), id_(id),
        action_points_(original.maxActionPoints()),
        hp_(original.maxHP()), money_(money) {
    map.allCharacters().add(this);
}

CharacterInstance::CharacterInstance(CharacterInstance&& other)
    : CharacterInstance(other.id_, other.original(), std::move(other.positionObj()),
                        other.map(), other.money_, std::move(other.items_)) {}

CharacterInstance::~CharacterInstance() {
    map().allCharacters().remove(id_);
}

int CharacterInstance::statCheckRoll(const std::string& stat, const DiceInterface& dice) const {
    return dice.roll(Dice::D20) + statBonus(stat);
}

int CharacterInstance::buffToStat(const std::string& stat) const {
    return std::accumulate(buffs_.begin(), buffs_.end(), 0,
        [&stat] (int res, const Buff& buff) {
            return buff.hasStat(stat) ? res + buff.stat(stat) : res;
    });
}

int CharacterInstance::statTotal(const std::string& stat_name) const {
    return original().stat(stat_name) + buffToStat(stat_name);
}

int8_t CharacterInstance::statBonus(const std::string& stat) const {
    return StatBased::calculateStatBonus(statTotal(stat));
}

int CharacterInstance::armorClass() const {
    return original().baseArmorClass() + statBonus(Armor::kScaling);
}

const std::list<Buff>& CharacterInstance::buffs() const {
    return buffs_;
}

void CharacterInstance::addBuff(const Buff& buff) {
    buffs_.push_back(buff);
}

Storage<Skill_Instance>& CharacterInstance::skills() {
    return skills_;
}

SharedStorage<Item>& CharacterInstance::items() {
    return items_;
}

const ActivatableInterface* CharacterInstance::chooseActivatable(std::string_view action_type, size_t action_id) {
    if (action_type == "skill") {
        return skills_.safeGet(action_id);
    }
    return nullptr;
}

std::tuple<Activatable::Result, ErrorStatus>
    CharacterInstance::use(std::string_view action_type, size_t action_id,
                           const std::vector<Tile>& target, const DiceInterface* dice) {
    auto activatable = chooseActivatable(action_type, action_id);
    if (activatable == nullptr) {
        return std::make_tuple(Activatable::Result{}, ErrorStatus::NO_SUCH_ITEM);
    }

    uint8_t dice_roll_res = dice ? statCheckRoll(activatable->scalesBy(), *dice) : 0;
    return activatable->use(this, target, dice_roll_res);
}

ErrorStatus CharacterInstance::trade(CharacterInstance& with, Item* give, Item* get) {
    return ErrorStatus::UNKNOWN_ERROR;
}

SaleResult CharacterInstance::buyItem(std::string_view item_type, CharacterInstance& from,
                                      size_t item_id, size_t count) {
    return SaleResult{};
}

unsigned int CharacterInstance::actionPoints() {
    return action_points_;
}

void CharacterInstance::refreshActionPoints() {
    action_points_ = original().maxActionPoints();
}

float CharacterInstance::damageModifier(uint8_t damage_type) const {
    bool resists = original().isResistantTo(damage_type);
    bool vulnerable = original().isVulnerableTo(damage_type);

    if (resists && !vulnerable) {
        return Resistible::kResistModifier;
    }

    if (!resists && vulnerable) {
        return Resistible::kVulnerableModifier;
    }

    return 1;
}

void CharacterInstance::setActionPoints(unsigned int action_points) {
    action_points_ = std::min(action_points, original().maxActionPoints());
}

int CharacterInstance::money() {
    return money_;
}

void CharacterInstance::setMoney(int money) {
    money_ = money;
}

void CharacterInstance::gainMoney(int money) {
    money_ += money;
}

void CharacterInstance::healBy(unsigned int amount) {
    setHP(hp_ + amount);
}

void CharacterInstance::takeDamage(unsigned int amount) {
    hp_ -= amount;
}

void CharacterInstance::setHP(int value) {
    hp_ = min(value, static_cast<int>(original().maxHP()));
}

bool CharacterInstance::isAlive() {
    return hp_ > 0;
}

void CharacterInstance::resetHP() {
    hp_ = original().maxHP();
}

int CharacterInstance::hp() {
    return hp_;
}

Character& CharacterInstance::original() {
    return const_cast<Character&>(const_cast<const CharacterInstance*>(this)->original());
}

const GameEntity::Info& CharacterInstance::info() const {
    return original().info();
}

std::string& CharacterInstance::info(const std::string& key) {
    return original().info(key);
}

const std::string& CharacterInstance::name() const {
    return original().name();
}

void CharacterInstance::setName(std::string_view name) {
    original().setName(name);
}

size_t CharacterInstance::getImageId() const {
    return original().getImageId();
}

size_t CharacterInstance::id() const {
    return id_;
}

void CharacterInstance::setImage(size_t image_id) {
    original().setImage(image_id);
}

void CharacterInstance::onTurnStart() {
    refreshActionPoints();
    for (auto& [_, skill] : skills_) {
        skill.onTurnStart();
    }
}

void CharacterInstance::onTurnEnd() {
    for (auto it = buffs_.begin(); it != buffs_.end();) {
        auto next = std::next(it);
        it->onTurnEnd();
        if (it->turnsLeft() == 0) {
            buffs_.erase(it);
        }
        it = next;
    }
}

ErrorStatus CharacterInstance::moveTo(const Tile& tile) {
    unsigned int points_spent = centerPos().distance(tile);
    if (points_spent > actionPoints()) {
        return ErrorStatus::NO_ACTION_POINTS;
    }

    auto status = OnLocation::moveTo(tile);
    if (status != ErrorStatus::OK) {
        return status;
    }

    setActionPoints(actionPoints() - points_spent);
    return ErrorStatus::OK;
}

ErrorStatus CharacterInstance::setCharacteristic(const std::string& which, const SetterParam& to) {
    auto status = original().setCharacteristic(which, to);
    if (status != ErrorStatus::INVALID_SETTER) {
        return status;
    }

    auto value = std::get_if<int64_t>(&to);
    if (!value) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    if (which == "ap") {
        setHP(*value);
        return ErrorStatus::OK;
    } else if (which == "hp") {
        setActionPoints(*value);
        return ErrorStatus::OK;
    } else if (which == "money") {
        setMoney(*value);
        return ErrorStatus::OK;
    }

    return ErrorStatus::INVALID_SETTER;
}
}  // namespace DnD
