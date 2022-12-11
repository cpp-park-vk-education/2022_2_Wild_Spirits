#pragma once

#include <vector>

#include "GameEntity.hpp"
#include "Action.hpp"

namespace DnD {

class ActivatableInterface {
 public:
    struct Result {
        int action_points = 0;
        unsigned int resource_spent = 0;  // Consumable uses or spell points
        Storage<Action::Result> results;

        Result() = default;
        Result(int ap, unsigned int resource, const std::vector<Action::Result>& result);

        bool operator==(const Result& other) const;
        friend std::ostream& operator<<(std::ostream& out, const Result& other);
    };

    virtual unsigned int activateCost() const = 0;

    virtual const std::string& scalesBy() const = 0;

    virtual std::tuple<Result, ErrorStatus> use(CharacterInstance*, const std::vector<Tile>&,
                                                uint8_t dice_roll_res = 0) const = 0;
};

class Activatable : public ActivatableInterface {
 private:
    std::vector<Action> actions_;
    Tile target;
    unsigned int action_cost_;
    std::string scaling_;

 public:
    Activatable() = default;
    virtual ~Activatable() {}

    Activatable(const std::vector<Action>& actions, unsigned int action_cost, std::string_view scaling) :
        actions_(actions), action_cost_(action_cost), scaling_(scaling) {}

    Activatable(std::vector<Action>&& actions, unsigned int action_cost, std::string_view scaling) :
        actions_(std::move(actions)), action_cost_(action_cost), scaling_(scaling) {}
    
    void addEffect(int action, std::unique_ptr<Effect>&& effect) {
        actions_[action].addEffect(std::move(effect));
    }

    void removeEffect(size_t action, size_t effect) {
        actions_[action].removeEffect(effect);
    }

    void addAction(const Action& action) {
        actions_.push_back(action);
    }

    void addAction(Action&& action) {
        actions_.push_back(std::move(action));
    }

    void removeAction(size_t action) {
        actions_.erase(actions_.begin() + action);
    }

    std::vector<Action>& actions() {
        return actions_;
    }

    Action& action(size_t action) {
        return actions_[action];
    }

    unsigned int activateCost() const override{
        return action_cost_;
    }

    void setActivateCost(unsigned int action_cost) {
        action_cost_ = action_cost;
    }

    const std::string& scalesBy() const override {
        return scaling_;
    }

    void setScaling(const std::string& scaling) {
        scaling_ = scaling;
    }

    std::tuple<Result, ErrorStatus> use(CharacterInstance* actor, const std::vector<Tile>&,
                                                uint8_t dice_roll_res = 0) const override;
};
}  // namespace DnD
