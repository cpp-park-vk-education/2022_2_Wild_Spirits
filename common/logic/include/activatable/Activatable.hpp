#pragma once

#include <vector>

#include "GameEntity.hpp"
#include "Action.hpp"

namespace DnD {
class ActivatableInterface : virtual public Identifiable {
 public:
    struct Result {
     private:
        size_t char_id;

     public:
        uint8_t dice_roll_res = 0;
        int action_points = 0;
        unsigned int resource_spent = 0;  // Consumable uses or spell points
        Storage<Action::Result> results;

        Result() : char_id(0) {}
        Result(size_t id) : char_id(id) {}
        Result(size_t id, uint8_t dice_roll, int ap, unsigned int resource,
               const std::vector<Action::Result>& result);

        size_t id() const { return char_id; }

        bool operator==(const Result& other) const;
        friend std::ostream& operator<<(std::ostream& out, const Result& other);
    };

    virtual unsigned int activateCost() const = 0;

    virtual const std::string& scalesBy() const = 0;

    virtual std::tuple<Result, ErrorStatus> use(CharacterInstance*, const std::vector<Tile>&,
                                                uint8_t dice_roll_res = 0) const = 0;
};

class Activatable : public ActivatableInterface {
 public:
    enum class Cast {
        Tile,
        Self
    };

 private:
    std::vector<Action> actions_;
    Tile target;
    unsigned int action_cost_;
    std::string scaling_;
    Cast cast_type_;

 public:
    Activatable() = default;
    virtual ~Activatable() {}

    // virtual size_t id() const = 0;

    Activatable(const std::vector<Action>& actions, unsigned int action_cost,
                std::string_view scaling, Cast cast_type = Cast::Tile) :
        actions_(actions), action_cost_(action_cost), scaling_(scaling), cast_type_(cast_type) {}

    Activatable(std::vector<Action>&& actions, unsigned int action_cost,
                std::string_view scaling, Cast cast_type = Cast::Tile) :
        actions_(std::move(actions)), action_cost_(action_cost), scaling_(scaling), cast_type_(cast_type) {}

    void setCastType(Cast cast_type);
    Cast castType() const;

    void addEffect(size_t action, std::unique_ptr<Effect>&& effect) {
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

    bool canMiss() const;

    std::tuple<Result, ErrorStatus> use(CharacterInstance* actor, const std::vector<Tile>&,
                                                uint8_t dice_roll_res = 0) const override;
    
    // ErrorStatus setCharacteristic(const std::string& which, const GameEntity::SetterParam& to);
};
}  // namespace DnD
