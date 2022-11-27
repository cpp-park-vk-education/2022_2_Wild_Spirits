#pragma once

#include "Activatable.hpp"
#include "GameEntity.hpp"
#include "TurnBased.hpp"

class Skill : public GameEntity, public Activatable, public Temporal {
 private:
    unsigned int cooldown_;

 public:
    Skill() = default;

    Skill(size_t id, std::string_view name, int image_id,
          const std::vector<Action>& actions, unsigned int action_cost,
          std::string_view scaling, unsigned int cooldown, const Info& info = {}) :
        GameEntity(id, name, image_id, info),
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

    std::tuple<std::vector<ActionResult>, ErrorStatus> use(const std::vector<Tile>& tiles, uint8_t dice_res = 0) override {
        return Activatable::use(tiles);
    }
};
