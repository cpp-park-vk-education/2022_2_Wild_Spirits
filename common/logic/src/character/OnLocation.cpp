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

ErrorStatus OnLocation::moveTo(const Tile& tile) {
    return location().setPosition(*this, tile);
}
}  // namespace DnD
