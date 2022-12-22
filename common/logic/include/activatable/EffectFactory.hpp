#pragma once

#include "Effect.hpp"
#include "Damage.hpp"
#include "Buff.hpp"

namespace DnD {
class EffectFactory {
 public:
    static std::unique_ptr<Effect> create(int amount) {
        return std::make_unique<Heal>(amount);
    }

    static std::unique_ptr<Effect> create(int x, int y) {
        return std::make_unique<Move>(x, y);
    }

    static std::unique_ptr<Effect> create(const StatBased::Stats& stats, unsigned int turns) {
        return std::make_unique<Buff>(stats, turns);
    }

    static std::unique_ptr<Effect> create(DamageType damage_type, uint8_t die_type, size_t times) {
        return std::make_unique<DealDamage>(damage_type, die_type, times, std::make_unique<Dice>());
    }
};
}
