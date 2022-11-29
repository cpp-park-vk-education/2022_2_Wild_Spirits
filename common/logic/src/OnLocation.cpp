#include "OnLocation.hpp"

#include "GameMap.hpp"
#include "Location.hpp"

const Location& OnLocation::location() {
    return map_.locations().get(current_location_);
}

void setLocation(Location& loc) {}
