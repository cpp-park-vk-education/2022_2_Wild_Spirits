#pragma once

#include "Position.hpp"

#include <cstddef>
#include <memory>

namespace DnD {

class GameMap;
class Location;

class OnLocation : public Position {
 private:
    std::unique_ptr<Position> pos_;
    GameMap& map_;
    size_t current_location_;

    std::unique_ptr<Position> clone() const override {
        return std::make_unique<OnLocation>(*this);
    }

 public:
    OnLocation(std::unique_ptr<Position>&& pos, GameMap& map);

    OnLocation(const OnLocation& other);
    OnLocation& operator=(OnLocation& other) = delete;
    
    const Location& location();
    void setLocation(Location& loc);

    void setPosition(std::unique_ptr<Position>&& pos) {
        pos_ = std::move(pos);
    }

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
};
} // namespace DnD
