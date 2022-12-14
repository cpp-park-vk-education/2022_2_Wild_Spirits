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
};

class Weapon : public ActivatableItem {
 public:
    Weapon() = default;

    Weapon(size_t id, std::string_view name, int image_id, const std::vector<Action>& actions,
           unsigned int action_cost = 0, unsigned int cost = 0, std::string_view scaling = "",
           const Info& info = {}) :
        ActivatableItem(id, name, image_id, actions, action_cost, cost, scaling, info) {}
};

class Consumable : public ActivatableItem {
 private:
    unsigned int uses_;

 public:
    Consumable() = default;

    Consumable(size_t id, std::string_view name, int image_id, const std::vector<Action>& actions,
               unsigned int action_cost = 0, unsigned int uses = 0, unsigned int cost = 0,
               std::string_view scaling = "", const Info& info = {}) :
        ActivatableItem(id, name, image_id, actions, action_cost, cost, scaling, info),
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
}  // namespace DnD
