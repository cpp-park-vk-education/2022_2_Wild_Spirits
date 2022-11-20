#pragma once

#include "Effect.hpp"
#include "WithStats.hpp"
#include "TurnBased.hpp"

class Buff : public Effect, public WithStats, public Temporal {
 public:
    Buff(const WithStats::Stats& stats, unsigned int turns) :
        WithStats(stats), Temporal(turns) {}
    
    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }
};
