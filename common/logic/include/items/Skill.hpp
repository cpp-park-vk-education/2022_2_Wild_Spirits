#pragma once

#include "Activatable.hpp"
#include "GameEntity.hpp"
#include "TurnBased.hpp"

namespace DnD {
class Skill : public GameEntity, public Activatable {
 private:
    unsigned int cooldown_;

 public:
    Skill() = default;

    Skill(size_t id, std::string_view name, int image_id,
          const std::vector<Action>& actions, unsigned int action_cost,
          unsigned int cooldown, std::string_view scaling = "", const Info& info = {}) :
        GameEntity(id, name, image_id, info),
        Activatable(actions, action_cost, scaling),
        cooldown_(cooldown) {}

    unsigned int cooldown() const {
        return cooldown_;
    }

    void setCooldown(unsigned int cooldown) {
        cooldown_ = cooldown;
    }
};

class Skill_Instance : public Temporal {
 private:
    const Skill& original_;

 public:
    Skill_Instance(const Skill& skill) : Temporal(skill.cooldown()), original_(skill) {}

    void onTurnStart() override {
        Temporal::onTurnStart();
    }

    const Skill& original() const {
        return original_;
    }

    size_t id() const {
        return original_.id();
    }

    std::tuple<std::vector<Action::Result>, ErrorStatus> use(const std::vector<Tile>& tiles,
                                                             uint8_t dice_res = 0) const {
        return original_.use(tiles, dice_res);
    }
};
}  // namespace DnD
