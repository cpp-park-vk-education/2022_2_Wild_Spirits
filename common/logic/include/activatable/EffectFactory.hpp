#pragma once

#include "Effect.hpp"
#include "Damage.hpp"
#include "Buff.hpp"

class EffectFactory {
    static Effect* createEffect(int amount) {
        return new Heal(amount);
    }

    static Effect* createEffect(int x, int y) {
        return new Move(x, y);
    }

    static Effect* createEffect(const WithStats::Stats& stats, unsigned int turns) {
        return new Buff(stats, turns);
    }

    static Effect* createEffect(uint8_t damage_type, uint8_t die_type, size_t times) {
        return new DealDamage(new Damage(damage_type, die_type, times));
    }
};
