#include "Character.hpp"

#include <utility>

namespace DnD {
    Character::Character(size_t id, std::string_view name, size_t image_id, unsigned int max_hp,
              int exp, unsigned int ap, unsigned int ac, const Stats& stats, const Info& info) :
        GameEntity(id, name, image_id, info),
        Resistible(),
        StatBased(stats),
        exp_(exp),
        max_hp_(max_hp),
        max_action_points_(ap),
        base_armor_class_(ac) {}

    Character::Character(const Character& other) :
        Character(other.id(), other.name(), other.getImageId(), other.max_hp_,
                  other.exp_, other.maxActionPoints(), other.baseArmorClass(),
                  other.stats(), other.info()) {}

    Character::Character(Character&& other) :
        Character(other.id(), other.name(), other.getImageId(), other.max_hp_,
                  other.exp_, other.maxActionPoints(), other.baseArmorClass(),
                  std::move(other.stats()), std::move(other.info())) {}

    Character& Character::operator=(const Character& other) {
        auto tmp = other;
        swap(tmp);
        return *this;
    }

    Character& Character::operator=(Character&& other) {
        auto tmp = std::move(other);
        swap(tmp);
        return *this;
    }

    void Character::swap(Character& other) {
        GameEntity::swap(other);
        std::swap(exp_, other.exp_);
        std::swap(max_action_points_, other.max_action_points_);
        std::swap(max_hp_, other.max_hp_);
        std::swap(base_armor_class_, other.base_armor_class_);
    }

    ErrorStatus Character::setCharacteristic(const std::string& which, const SetterParam& to) {
        auto status = GameEntity::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        auto value = std::get_if<int64_t>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }

        if (which == "max-ap") {
            setMaxActionPoints(*value);
            return ErrorStatus::OK;
        } else if (which == "max-hp") {
            setMaxHP(*value);
            return ErrorStatus::OK;
        } else if (which == "base-armor") {
            setBaseArmorClass(*value);
            return ErrorStatus::OK;
        }

        return ErrorStatus::INVALID_SETTER;
    }
}  // namespace DnD
