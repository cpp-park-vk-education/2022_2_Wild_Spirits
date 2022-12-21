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

const ActivatableInterface* PlayerCharacter::chooseActivatable(std::string_view action_type, size_t action_id) {
    std::unordered_map<std::string_view, std::function<const ActivatableInterface*(size_t)>> get_action = {
        {"skill", [this] (size_t id) { return skills_.safeGet(id); }},
        {"weapon", [this] (size_t id) { return weapons_.safeGet(id).get(); }},
        {"consumable", [this] (size_t id) { return consumables_.safeGet(id); }},
        {"spell", [this] (size_t id) { return spells_.safeGet(id).get(); }},
    };

    if (get_action.contains(action_type)) {
        return get_action[action_type](action_id);
    }
    return nullptr;
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
