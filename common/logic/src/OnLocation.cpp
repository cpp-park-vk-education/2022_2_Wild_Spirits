#include "OnLocation.hpp"

#include "GameMap.hpp"
#include "Location.hpp"

const Location& OnLocation::location() {
    return map_.getLocation(current_location_);
}
