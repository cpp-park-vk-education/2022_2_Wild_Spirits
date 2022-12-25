#include "ActivatableItem.hpp"

namespace DnD {
    ErrorStatus Item::setCharacteristic(const std::string& which, const SetterParam& to) {
        auto status = GameEntity::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        auto value = std::get_if<int64_t>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }

        if (which == "cost") {
            setCost(*value);
            return ErrorStatus::OK;
        }

        return ErrorStatus::INVALID_SETTER;
    }

    ErrorStatus ActivatableItem::setCharacteristic(const std::string& which, const SetterParam& to) {
        auto status = Item::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        status = Activatable::setCharacteristic(which, to);
        return status;
    }

    ErrorStatus Consumable::setCharacteristic(const std::string& which, const SetterParam& to) {
        auto value = std::get_if<int64_t>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }

        if (which == "uses") {
            setUses(*value);
            return ErrorStatus::OK;
        }

        return ErrorStatus::INVALID_SETTER;
    }

    std::tuple<Activatable::Result, ErrorStatus> Consumable::use(CharacterInstance* actor,
                                                const std::vector<Tile>& targets,
                                                uint8_t dice_roll_res) const {
        if (uses_ == 0) {
            return std::make_tuple(Result{}, ErrorStatus::NO_USES_LEFT);
        }

        auto result = original().use(actor, targets, dice_roll_res);
        std::get<Result>(result).resource_spent = 1;
        return result;
    }
}  // namespace DnD
