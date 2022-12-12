#include "Skill.hpp"

namespace DnD {
    ErrorStatus Skill::setCharacteristic(const std::string& which, const SetterParam& to) {
        auto status = GameEntity::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        status = Activatable::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        auto value = std::get_if<int64_t>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }

        if (which == "cooldown") {
            setCooldown(*value);
            return ErrorStatus::OK;
        }

        return ErrorStatus::INVALID_SETTER;
    }

    std::tuple<Activatable::Result, ErrorStatus> Skill_Instance::use(CharacterInstance* actor,
                                        const std::vector<Tile>& tiles,
                                        uint8_t dice_roll_res) const {
        if (turnsLeft() != 0) {
            return std::make_tuple(Result{}, ErrorStatus::SKILL_ON_COOLDOWN);
        }
        const_cast<Skill_Instance*>(this)->reset(original_->cooldown());
        return original_->use(actor, tiles, dice_roll_res);
    }
}  // namespace DnD
