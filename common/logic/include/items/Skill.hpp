#pragma once

#include "Activatable.hpp"
#include "GameEntity.hpp"
#include "TurnBased.hpp"

class Skill : public GameEntity, public Activatable, public Temporal {
 private:
    unsigned int cooldown_;

 public:
    Skill() = default;

    Skill(std::string_view name, int image_id, const Info& info,
          const std::vector<Action>& actions, unsigned int action_cost,
          std::string_view scaling, unsigned int cooldown) :
        GameEntity(name, image_id, info),
        Activatable(actions, action_cost, scaling),
        cooldown_(cooldown) {}

    unsigned int cooldown() {
        return cooldown_;
    }

    void setCooldown(unsigned int cooldown) {
        cooldown_ = cooldown;
    }

    void onTurnStart() override {
        Temporal::onTurnStart();
    }

    std::tuple<std::vector<Action::Result>, ErrorStatus> getResults(const std::vector<Tile>& tiles) override {
        return Activatable::getResults(tiles);
    }
};
