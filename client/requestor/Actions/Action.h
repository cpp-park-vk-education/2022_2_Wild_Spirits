#pragma once

#include <cstddef>
#include <cstdint>

namespace LM {

    class Action {
    public:
        enum class Type : uint32_t {
            kMove = 0,
            kUseWeapon,
            kUseConsumable,
            kUseSkill,
            kUseSpell,
        };

    public:
        virtual Type getType() const = 0;
    };

}    // namespace LM
