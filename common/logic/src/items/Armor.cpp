#include "Armor.hpp"

namespace DnD {
    ErrorStatus Armor::setCharacteristic(const std::string& which, const SetterParam& to) {
        auto status = Item::setCharacteristic(which, to);
        if (status != ErrorStatus::INVALID_SETTER) {
            return status;
        }

        auto value = std::get_if<int64_t>(&to);
        if (!value) {
            return ErrorStatus::INVALID_ARGUMENT;
        }

        if (which == "defense") {
            setDefense(*value);
            return ErrorStatus::OK;
        } else if (which == "type") {
            setArmorType(static_cast<Type>(*value));
            return ErrorStatus::OK;
        }

        return ErrorStatus::INVALID_SETTER;
    }
}  // namespace DnD
