#include "PlayerCharacter.hpp"

namespace DnD {
PlayerCharacter::PlayerCharacter(size_t id, Character&& original,
                                 std::unique_ptr<Position>&& pos, GameMap& map,
                                 std::shared_ptr<const Class> char_class, std::shared_ptr<const Race> race,
                                 int money, const SharedStorage<Item>& items) :
        CharacterInstance(id, original, std::move(pos), map, money, items),
        base_(std::move(original)),
        class_list_(),
        race_(race) {
    class_list_.add(char_class);
    for (auto& skill : char_class->skills()) {
        skills_.add(Skill_Instance(skill));
    }
}

int PlayerCharacter::armorClass() const {
    if (!armor_) {
        return base_.baseArmorClass();
    }

    int base = armor_->defense();

    switch (armor_->armorType()) {
        case Armor::Type::Light:
            return base + statBonus(Armor::kScaling);
        case Armor::Type::Medium:
            return base + std::min(Armor::kMaxBonus, statBonus(Armor::kScaling));
        default:
            return base;
    }
}

unsigned int PlayerCharacter::gainXP(unsigned int exp) {
    current_exp_ += exp;
    if (current_exp_ >= base_.exp()) {
        unsigned int levels_upped = current_exp_ / base_.exp();
        current_exp_ %= base_.exp();
        return levels_upped;
    }
    return 0;
}

ErrorStatus PlayerCharacter::moveTo(const Tile& tile) {
    unsigned int points_spent = centerPos().distance(tile);
    if (points_spent > actionPoints()) {
        return ErrorStatus::NO_ACTION_POINTS;
    }

    setActionPoints(actionPoints() - points_spent);
    return OnLocation::moveTo(tile);
}

const ActivatableInterface* PlayerCharacter::chooseActivatable(std::string_view action_type, size_t action_id) {
    static std::unordered_map<std::string_view, std::function<const ActivatableInterface*(size_t)>> get_action = {
        {"skill", [this] (size_t id) { return skills_.safeGet(id); }},
        {"weapon", [this] (size_t id) { return weapons_.safeGet(id).get(); }},
        {"consumable", [this] (size_t id) { return consumables_.safeGet(id); }}
    };

    if (get_action.contains(action_type)) {
        return get_action[action_type](action_id);
    }
    return nullptr;
}

std::tuple<Activatable::Result, ErrorStatus>
    PlayerCharacter::use(std::string_view action_type, size_t action_id,
                         const std::vector<Tile>& target, const DiceInterface* dice) {
    if (action_type == "spell") {
        auto spell = spells_.safeGet(action_id);

        if (spell == nullptr) {
            return std::make_tuple(Activatable::Result{}, ErrorStatus::NO_SUCH_ITEM);
        }

        if (spellPoints() < spell->cost()) {
            return std::make_tuple(Activatable::Result{}, ErrorStatus::NO_SPELL_POINTS);
        }

        spell_points_ -= spell->cost();

        uint8_t dice_roll_res = dice ? statCheckRoll(spell->scalesBy(), *dice) : 0;
        return spell->use(this, target, dice_roll_res);
    }

    return CharacterInstance::use(action_type, action_id, target, dice);
}

ErrorStatus PlayerCharacter::setCharacteristic(const std::string& which, const SetterParam& to) {
    auto status = CharacterInstance::setCharacteristic(which, to);
    if (status != ErrorStatus::INVALID_SETTER) {
        return status;
    }

    auto value = std::get_if<int64_t>(&to);
    if (!value) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    if (which == "sp") {
        setSpellPoints(*value);
        return ErrorStatus::OK;
    } else if (which == "max-sp") {
        setMaxSpellPoints(*value);
        return ErrorStatus::OK;
    }

    return ErrorStatus::INVALID_SETTER;
}
}  // namespace DnD
