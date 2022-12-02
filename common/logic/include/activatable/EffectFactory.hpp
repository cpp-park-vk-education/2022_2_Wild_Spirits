#pragma once

#include "Effect.hpp"
#include "Damage.hpp"
#include "Buff.hpp"

namespace DnD {
class EffectFactory {
    static Effect* create(int amount) {
        return new Heal(amount);
    }

    static Effect* create(int x, int y) {
        return new Move(x, y);
    }

    static Effect* create(const StatBased::Stats& stats, unsigned int turns) {
        return new Buff(stats, turns);
    }

    static Effect* create(uint8_t damage_type, uint8_t die_type, size_t times) {
        return new DealDamage(damage_type, die_type, times, new Dice());
    }
};
}
