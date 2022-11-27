#pragma once

#include "Activatable.hpp"

class Spell : public GameEntity, public Activatable {
 private:
    unsigned int spell_cost_;

 public:
    Spell() = default;

    Spell(std::string_view name, int image_id,
          const std::vector<Action>& actions, unsigned int action_cost,
          std::string_view scaling, unsigned int spell_cost, const Info& info = {}) :
        GameEntity(name, image_id, info),
        Activatable(actions, action_cost, scaling),
        spell_cost_(spell_cost) {}

    unsigned int cost() {
        return spell_cost_;
    }

    void setCost(unsigned int spell_cost) {
        spell_cost_ = spell_cost;
    }
};
