#include "Spell.hpp"

namespace DnD {
    ErrorStatus Spell::setCharacteristic(const std::string& which, const SetterParam& to) {
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

        if (which == "sp-cost") {
            setCost(*value);
            return ErrorStatus::OK;
        }

        return ErrorStatus::INVALID_SETTER;
    }
}  // namespace DnD
