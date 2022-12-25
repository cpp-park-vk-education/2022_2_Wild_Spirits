#include "OnLocation.hpp"

#include "GameMap.hpp"
#include "Location.hpp"

namespace DnD {
OnLocation::OnLocation(std::unique_ptr<Position>&& pos, GameMap& map, size_t location_id) :
        pos_(std::move(pos)), map_(map),
        current_location_(location_id == kNoLocationPassed ? map.currentLocationId() : location_id) {}

OnLocation::OnLocation(const OnLocation& other) : OnLocation(other.pos_->clone(), other.map_) {}

Location& OnLocation::location() const {
    return map_.locations().get(current_location_);
}

void OnLocation::setLocation(size_t loc_id) {
    current_location_ = loc_id;
}

ErrorStatus OnLocation::setPosition(std::unique_ptr<Position>&& pos) {
    if (pos_) {
        location().removeObject(*this);
    }

    pos_ = std::move(pos);
    location().addObject(*this);
}

std::vector<Tile> OnLocation::occupiedTiles() const {
    if (!pos_) {
        return std::vector<Tile>{};
    }
    return pos_->occupiedTiles();
}

std::vector<Tile> OnLocation::actualOccupied() const {
    std::vector<Tile> original = pos_->occupiedTiles();
    std::vector<Tile> res(original.size());

    std::copy_if(original.begin(), original.end(), res.begin(),
        [this] (const Tile& tile) { return location().isInBounds(tile); });
    return res;
}

ErrorStatus OnLocation::moveTo(const Tile& tile) {
    return location().setPosition(*this, tile);
}

ErrorStatus OnLocation::moveBy(int x, int y) {
    return moveTo(mapPosition()[0] + Offset{x, y});
}

ErrorStatus OnLocation::moveToApproximately(const Tile& tile) {
    auto [res_tile, status] = location().closestFreeTile(*this, tile, true);
    if (status != ErrorStatus::OK) {
        return status;
    }
    moveTo(res_tile);
    return ErrorStatus::OK;
}
}  // namespace DnD
