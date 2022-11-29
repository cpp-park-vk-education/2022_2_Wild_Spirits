#include "OnLocation.hpp"

#include "GameMap.hpp"
#include "Location.hpp"

OnLocation::OnLocation(Position* pos, GameMap& map) :
        pos_(pos), map_(map), current_location_(map.currentLocationId()) {}
    
OnLocation::OnLocation(const OnLocation& other) : OnLocation(other.pos_->clone(), other.map_) {}

const Location& OnLocation::location() {
    return map_.locations().get(current_location_);
}

void setLocation(Location& loc) {}
