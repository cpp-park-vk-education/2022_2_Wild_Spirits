#pragma once

#include "Effect.hpp"
#include "StatBased.hpp"
#include "TurnBased.hpp"

namespace DnD {
class Buff : public Effect, public StatBased, public Temporal {
 private:
    std::string statsToStr() const;

 public:
    Buff() : Temporal(0) {}
    Buff(const StatBased::Stats& stats, unsigned int turns) : StatBased(stats), Temporal(turns) {}

    std::string info() const override {
        return "Provide buffs for " + std::to_string(turnsLeft()) + " turns:\n" + statsToStr();
    }

    std::unique_ptr<Effect>clone() const override {
        return std::make_unique<Buff>(*this);
    }

    void updateActionResult(const CharacterInstance& character, Action::Result* result) const override;
};
}  // namespace DnD