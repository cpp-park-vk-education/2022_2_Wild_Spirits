#pragma once

#include <variant>

#include "ErrorStatus.hpp"

namespace DnD {
    class DynamiclySettable {
     protected:
        using SetterParam = std::variant<std::string, int64_t>;
     public:
        virtual ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) = 0;
    };
}  // namespace DnD
