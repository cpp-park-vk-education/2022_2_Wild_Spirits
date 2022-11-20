#pragma once

#include "Location.hpp"

class GameState;

class GameMap {
 private:
    std::unordered_map<size_t, Location> locations_;
    size_t current_location_;
    GameState& game_;

 public:
    GameMap(GameState& game) : game_(game) {}

    void addLocation(size_t id, const Location& location) {
        locations_[id] = location;
    }

    void removeLocation();

    void switchLocation(size_t id);

    void switchLocation(size_t char_id, size_t id);

    Location& currentLocation() {
        return locations_[current_location_];
    }

    size_t currentLocationId() const {
        return current_location_;
    }

    const Location& getLocation(size_t location_id) const {
        return locations_.at(location_id);
    }
};
