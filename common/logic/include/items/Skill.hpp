#pragma once

#include "Activatable.hpp"
#include "TurnBased.hpp"

class Skill : public Activatable, public Temporal {
 private:
    unsigned int cooldown_;

 public:
    Skill();

    unsigned int cooldown() {
        return cooldown_;
    }

    void setCooldown(unsigned int cooldown) {
        cooldown_ = cooldown;
    }

    void onTurnStart() override {
        Temporal::onTurnStart();
    }

    Action::Result getResult(const std::vector<Tile>& tiles) override {
        return Activatable::getResult(tiles);
    }
};
