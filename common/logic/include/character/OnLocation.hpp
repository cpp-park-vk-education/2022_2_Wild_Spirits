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

 protected:
    std::unique_ptr<Position>& positionObj() {
        return pos_;
    }

 public:
    OnLocation(std::unique_ptr<Position>&& pos, GameMap& map);

    OnLocation(const OnLocation& other);
    OnLocation& operator=(OnLocation& other) = delete;
    
    Location& location() const;

    size_t locationId() const {
        return current_location_;
    }

    virtual void setLocation(Location& loc);

    void setPosition(std::unique_ptr<Position>&& pos) {
        pos_ = std::move(pos);
    }

    bool isInArea(const Area& area) const override {
        return pos_->isInArea(area);
    }

    std::array<Tile, 2> mapPosition() const override {
        return pos_->mapPosition();
    }

    Tile centerPos() const override {
        return pos_->centerPos();
    }

    ErrorStatus moveTo(const Tile& tile) override;

    void moveBy(int x, int y) override {
        return pos_->moveBy(x, y);
    }

    GameMap& map() const {
        return map_;
    }
};
} // namespace DnD
