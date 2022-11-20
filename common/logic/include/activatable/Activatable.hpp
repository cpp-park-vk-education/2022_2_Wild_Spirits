#pragma once

#include <vector>

#include "GameEntity.hpp"
#include "Action.hpp"

class Activatable : virtual public GameEntity {
 private:
    std::vector<Action> actions_;
    Tile target;
    CharacterInstance* actor_;
    unsigned int action_cost_;
    std::string scaling_;

 public:
    Activatable(std::string_view name, int image_id, const Info& info,
                const std::vector<Action>& actions, unsigned int action_cost, std::string_view scaling) :
        GameEntity(name, image_id, info), actions_(actions), action_cost_(action_cost), scaling_(scaling) {} 

    void addEffect(int action, Effect* effect) {
        actions_[action].addEffect(effect);
    }

    void removeEffect(size_t action, size_t effect) {
        actions_[action].removeEffect(effect);
    }

    void addAction(const Action& action) {
        actions_.push_back(action);
    }

    void removeAction(size_t action) {
        actions_.erase(actions_.begin() + action);
    }

    Action& action(size_t action) {
        return actions_[action];
    }

    void setActor(CharacterInstance* actor) {
        actor_ = actor;
    }

    unsigned int activateCost() {
        return action_cost_;
    }

    void setActivateCost(unsigned int action_cost) {
        action_cost_ = action_cost;
    }

    virtual Action::Result getResult(const std::vector<Tile>&) {
        return Action::Result{};
    }
};
