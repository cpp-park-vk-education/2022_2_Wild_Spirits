#include "OnLocation.hpp"

#include "GameMap.hpp"
#include "Location.hpp"

namespace DnD {
OnLocation::OnLocation(std::unique_ptr<Position>&& pos, GameMap& map) :
        pos_(std::move(pos)), map_(map), current_location_(map.currentLocationId()) {}

OnLocation::OnLocation(const OnLocation& other) : OnLocation(other.pos_->clone(), other.map_) {}

Location& OnLocation::location() const {
    return map_.locations().get(current_location_);
}

void OnLocation::setLocation(Location& loc) {
    current_location_ = loc.id();
}
}  // namespace DnD
