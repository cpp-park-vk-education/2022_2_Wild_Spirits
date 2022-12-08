#pragma once

#include "Activatable.hpp"
#include "Item.hpp"

namespace DnD {
class ActivatableItem : public Item, public Activatable {
 public:
    ActivatableItem() = default;

    ActivatableItem(size_t id, std::string_view name, int image_id,
                    const std::vector<Action>& actions, unsigned int action_cost = 0, 
                    unsigned int cost = 0, std::string_view scaling = "",
                    const Info& info = {}) :
        Item(id, name, image_id, cost, info),
        Activatable(actions, action_cost, scaling) {}

    ActivatableItem(size_t id, std::string_view name, int image_id,
                    std::vector<Action>&& actions, unsigned int action_cost = 0, 
                    unsigned int cost = 0, std::string_view scaling = "",
                    const Info& info = {}) :
        Item(id, name, image_id, cost, info),
        Activatable(std::move(actions), action_cost, scaling) {}
};

class Weapon : public ActivatableItem {
 public:
    Weapon() = default;

    Weapon(size_t id, std::string_view name, int image_id, const std::vector<Action>& actions,
           unsigned int action_cost = 0, unsigned int cost = 0, std::string_view scaling = "",
           const Info& info = {}) :
        ActivatableItem(id, name, image_id, actions, action_cost, cost, scaling, info) {}

    Weapon(size_t id, std::string_view name, int image_id, std::vector<Action>&& actions,
           unsigned int action_cost = 0, unsigned int cost = 0, std::string_view scaling = "",
           const Info& info = {}) :
        ActivatableItem(id, name, image_id, std::move(actions), action_cost, cost, scaling, info) {}
};

class Consumable : public ActivatableInterface {
 private:
    const ActivatableItem& original_;
    unsigned int uses_;

 public:
    Consumable() = default;

    Consumable(const ActivatableItem& item, unsigned int uses) : original_(item), uses_(uses) {}
    
    void add(unsigned int num) {
        uses_ += num;
    }

    size_t id() const {
        return original_.id();
    }

    const ActivatableItem& original() const {
        return original_;
    }

    unsigned int usesLeft() {
        return uses_;
    }

    bool empty() {
        return uses_ == 0;
    }

    unsigned int activateCost() const override {
        return original_.activateCost();
    }

    const std::string& scalesBy() const override {
        return original_.scalesBy();
    }

    std::tuple<Result, ErrorStatus> use(CharacterInstance* actor, const std::vector<Tile>& targets,
                                                uint8_t dice_roll_res = 0) const override {
        if (uses_ == 0) {
            return std::make_tuple(Result{}, ErrorStatus::NO_USES_LEFT);
        }

        const_cast<Consumable*>(this)->uses_ -= 1;

        auto result = original_.use(actor, targets, dice_roll_res);
        std::get<Result>(result).resource_spent = 1;
        return result;
    }
};
}  // namespace DnD
