#pragma once

#include "GameEntity.hpp"

class Item : virtual public GameEntity {
 private:
    int cost_;

 public:
    Item() = default;

    Item(std::string_view name, int image_id, const Info& info, int cost) :
        GameEntity(name, image_id, info), cost_(cost) {}
    
    int cost() const {
        return cost_;
    }

    void setCost(int cost) {
        cost_ = cost;
    }
};
