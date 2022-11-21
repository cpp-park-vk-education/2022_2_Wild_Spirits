#pragma once

#include <cstdint>

namespace LM {

    class Action {
    public:
        enum class Type : uint32_t {
            kUseWeapon = 0,
            kUseConsumable,
            kUseSkill,
            kUseSpell,
        };
    public:
        virtual Type getType() const = 0;
    };

}
