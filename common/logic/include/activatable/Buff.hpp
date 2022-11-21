#pragma once

#include "Effect.hpp"
#include "StatBased.hpp"
#include "TurnBased.hpp"

class Buff : public Effect, public StatBased, public Temporal {
 public:
    Buff(const StatBased::Stats& stats, unsigned int turns) :
        StatBased(stats), Temporal(turns) {}
    
    Result getResult(const CharacterInstance& character) const override {
        return Result{};
    }
};
