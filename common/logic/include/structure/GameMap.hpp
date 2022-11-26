#pragma once

#include "Location.hpp"

class GameState;
class PlayerCharacter;

class GameMap {
 public:
    virtual void addLocation(size_t id, const Location& location) = 0;

    virtual void removeLocation(size_t id) = 0;

    virtual void switchLocation(size_t id) = 0;

    virtual void switchLocation(size_t char_id, size_t id) = 0;

    virtual Location& currentLocation() = 0;

    virtual size_t currentLocationId() const = 0;

    virtual const Location& getLocation(size_t id) const = 0;

    virtual Storage<PlayerCharacter>& players() = 0;

    virtual ~GameMap() {}
};

class GameMapImpl : public GameMap {
 private:
    std::unordered_map<size_t, Location> locations_;
    size_t current_location_;
    GameState& game_;

 public:
    GameMapImpl(GameState& game) : game_(game) {}

    void addLocation(size_t id, const Location& location) {
        locations_[id] = location;
    }

    void removeLocation(size_t id);

    void switchLocation(size_t id);

    void switchLocation(size_t char_id, size_t id);

    Location& currentLocation() {
        return locations_[current_location_];
    }

    size_t currentLocationId() const {
        return current_location_;
    }

    const Location& getLocation(size_t id) const {
        return locations_.at(id);
    }

    Storage<PlayerCharacter>& players();
};
