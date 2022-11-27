#pragma once

#include "GameEntity.hpp"

class Item : public GameEntity {
 private:
    int cost_;

 public:
    Item() = default;

    Item(std::string_view name, int image_id, int cost, const Info& info = {}) :
        GameEntity(name, image_id, info), cost_(cost) {}
    
    int cost() const {
        return cost_;
    }

    void setCost(int cost) {
        cost_ = cost;
    }
};
