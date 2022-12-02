#pragma once

#include "Position.hpp"

#include <cstddef>

namespace DnD {
class GameMap;
class Location;

class OnLocation : public Position {
 private:
    Position* pos_;
    GameMap& map_;
    size_t current_location_;

    Position* clone() const override {
        return new OnLocation(*this);
    }

 public:
    OnLocation(Position* pos, GameMap& map);

    OnLocation(const OnLocation& other);
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
} // namespace DnD
