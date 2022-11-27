#pragma once

#include "Effect.hpp"
#include "StatBased.hpp"
#include "TurnBased.hpp"

class Buff : public Effect, public StatBased, public Temporal {
 public:
    Buff() : Temporal(0) {}
    Buff(const StatBased::Stats& stats, unsigned int turns) : StatBased(stats), Temporal(turns) {}

    Effect* clone() const override {
        return new Buff(*this);
    }

    void updateActionResult(const CharacterInstance& character, ActionResult* result) const override;
};
