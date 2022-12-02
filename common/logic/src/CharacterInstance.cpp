#include "CharacterInstance.hpp"

#include "Dice.hpp"
#include "Item.hpp"
#include "Action.hpp"

namespace DnD {
CharacterInstance::CharacterInstance(size_t id, Character& original, Position* pos, GameMap& map,
                      int money, std::unordered_map<size_t, Item*> items) :
        OnLocation(pos, map),
        original_(original), items_(items), id_(id),
        action_points_(original.maxActionPoints()),
        hp_(original.maxHP()), money_(money) {}

int CharacterInstance::statCheckRoll(std::string_view stat) const {
    return 0;
}

int CharacterInstance::statBonus(std::string_view) const {
    return 0;
}

int CharacterInstance::armorClass() const {
    return 0;
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

Storage<Item*>& CharacterInstance::items() {
    return items_;
}

std::tuple<std::vector<Action::Result>, ErrorStatus>
    CharacterInstance::use(std::string_view action_type, size_t action_id,
                   const std::vector<Tile>& target, const DiceInterface*) {
    return Action().getResults(*this, {});
}

ErrorStatus CharacterInstance::trade(CharacterInstance& with, Item* give, Item* get) {
    return ErrorStatus::Fail();
}

SaleResult CharacterInstance::buyItem(std::string_view item_type, CharacterInstance& from,
                                      size_t item_id, size_t count) {
    return SaleResult{};
}

unsigned int CharacterInstance::actionPoints() {
    return action_points_;
}

void CharacterInstance::refreshActionPoints() {
    action_points_ = original_.maxActionPoints();
}

void CharacterInstance::setActionPoints(unsigned int action_points) {
    action_points_ = std::min(action_points, original_.maxActionPoints());
}

int CharacterInstance::money() {
    return money_;
}

void CharacterInstance::gainMoney(int money) {
    money_ += money;
}

void CharacterInstance::healBy(unsigned int amount) {
    hp_ += amount;
}

void CharacterInstance::takeDamage(unsigned int amount) {
    hp_ -= amount;
}

bool CharacterInstance::isAlive() {
    return hp_ > 0;
}

void CharacterInstance::resetHP() {
    hp_ = original_.maxHP();
}

int CharacterInstance::hp() {
    return hp_;
}

const std::string& CharacterInstance::info(const std::string& key) const {
    return original_.info(key);
}

std::string& CharacterInstance::info(const std::string& key) {
    return original_.info(key);
}

const std::string& CharacterInstance::name() const {
    return original_.name();
}

void CharacterInstance::setName(std::string_view name) {
    original_.setName(name);
}

size_t CharacterInstance::getImageId() const {
    return original_.getImageId();
}

size_t CharacterInstance::id() const {
    return id_;
}

void CharacterInstance::setImage(size_t image_id) {
    original_.setImage(image_id);
}

void CharacterInstance::onTurnStart() {}
}  // namespace DnD
