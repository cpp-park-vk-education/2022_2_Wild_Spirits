#pragma once

#include "Position.hpp"

#include <cstddef>
#include <memory>
#include <limits>

namespace DnD {

class GameMap;
class Location;

class OnLocation : public Position {
 private:
    static constexpr size_t kNoLocationPassed = std::numeric_limits<unsigned int>::max();

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
    OnLocation(GameMap& map) : map_(map) {}

    OnLocation(std::unique_ptr<Position>&& pos, GameMap& map, size_t location_id = kNoLocationPassed);

    OnLocation(const OnLocation& other);
    OnLocation& operator=(OnLocation& other) = delete;

    Location& location() const;

    size_t locationId() const {
        return current_location_;
    }

    virtual void setLocation(size_t loc_id);

    ErrorStatus setPosition(std::unique_ptr<Position>&& pos);

    bool isInArea(const Area& area) const override {
        return pos_->isInArea(area);
    }

    std::array<Tile, 2> mapPosition() const override {
        return pos_->mapPosition();
    }

    Tile centerPos() const override {
        return pos_->centerPos();
    }

    std::vector<Tile> occupiedTiles() const override;

    std::vector<Tile> actualOccupied() const;

    ErrorStatus moveTo(const Tile& tile) override;
    ErrorStatus moveBy(int x, int y) override;

    ErrorStatus moveToApproximately(const Tile& tile);

    GameMap& map() const {
        return map_;
    }

    friend class Location;
};
} // namespace DnD
