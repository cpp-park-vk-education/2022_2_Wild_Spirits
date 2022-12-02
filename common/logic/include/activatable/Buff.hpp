#pragma once

#include "Effect.hpp"
#include "StatBased.hpp"
#include "TurnBased.hpp"

namespace DnD {
class Buff : public Effect, public StatBased, public Temporal {
 public:
    Buff() : Temporal(0) {}
    Buff(const StatBased::Stats& stats, unsigned int turns) : StatBased(stats), Temporal(turns) {}

    std::string info() const override {
        return "";
    }

    Effect* clone() const override {
        return new Buff(*this);
    }

    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override;
};
}  // namespace DnD