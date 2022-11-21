#pragma once

#include "Position.hpp"

#include <cstddef>

class GameMap;
class Location;

class OnLocation : public Position {
 private:
    Position* pos_;
    const GameMap& map_;
    size_t current_location_;

 public:
    OnLocation(Position* pos, GameMap& map) :
        pos_(pos), map_(map) {}
    
    const Location& location();

    bool isInArea(Area* area) override {
        return pos_->isInArea(area);
    }

    std::tuple<Tile, Tile> mapPosition() override {
        return pos_->mapPosition();
    }

    void moveTo(const Tile& tile) override {
        return pos_->moveTo(tile);
    }

    void moveBy(int x, int y) override {
        return pos_->moveBy(x, y);
    }

    ~OnLocation() {
        delete pos_;
    }
};
