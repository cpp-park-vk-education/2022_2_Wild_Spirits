#pragma once

#include "Position.hpp"

#include <cstddef>

class GameMap;
class Location;

class OnLocation : public Position {
 private:
    Position* pos_;
    GameMap& map_;
    size_t current_location_;

    Position* clone() const override {
        return new OnLocation(pos_->clone(), map_);
    }

 public:
    OnLocation(Position* pos, GameMap& map) :
        pos_(pos), map_(map) {}
    
    OnLocation(const OnLocation& other) = delete;
    OnLocation& operator=(OnLocation& other) = delete;
    
    const Location& location();
    void setLocation(Location& loc);

    bool isInArea(const Area& area) override {
        return pos_->isInArea(area);
    }

    std::pair<Tile, Tile> mapPosition() override {
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
