#pragma once

#include "Activatable.hpp"
#include "Item.hpp"

class ActivatableItem : public Item, public Activatable {
 public:
    ActivatableItem() = default;

    ActivatableItem(std::string_view name, int image_id, const Info& info,
                    const std::vector<Action>& actions, unsigned int action_cost, 
                    unsigned int cost = 0, std::string_view scaling = "") :
        Item(name, image_id, info, cost),
        Activatable(actions, action_cost, scaling) {}
};

class Weapon : public ActivatableItem {
 public:
    Weapon() = default;

    Weapon(std::string_view name, int image_id, const Info& info,
                const std::vector<Action>& actions, unsigned int action_cost, 
                unsigned int cost = 0, std::string_view scaling = "") :
        ActivatableItem(name, image_id, info, actions, action_cost, cost, scaling) {}
};

class Consumable : public ActivatableItem {
 private:
    unsigned int uses_;

 public:
    Consumable() = default;

    Consumable(std::string_view name, int image_id, const Info& info,
               const std::vector<Action>& actions, unsigned int action_cost, 
               unsigned int uses = 0, unsigned int cost = 0, std::string_view scaling = "") :
        ActivatableItem(name, image_id, info, actions, action_cost, cost, scaling),
        uses_(uses) {}
    
    void add(unsigned int num) {
        uses_ += num;
    }

    void use(unsigned int num) {
        if (num > uses_) {
            uses_ = 0;
            return;
        }

        uses_ -= num;
    }

    unsigned int usesLeft() {
        return uses_;
    }

    bool empty() {
        return uses_ == 0;
    }
};
