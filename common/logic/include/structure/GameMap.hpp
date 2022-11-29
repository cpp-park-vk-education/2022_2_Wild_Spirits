#pragma once

#include "Location.hpp"

class GameState;
class PlayerCharacter;

class GameMap {
 public:
    virtual Storage<Location>& locations() = 0;

    virtual void switchLocation(size_t id) = 0;
    virtual void switchLocation(size_t char_id, size_t id) = 0;

    virtual Location& currentLocation() = 0;
    virtual size_t currentLocationId() const = 0;

    virtual Storage<PlayerCharacter>& players() = 0;

    virtual ~GameMap() {}
};

class GameMapImpl : public GameMap {
 private:
    Storage<Location> locations_;
    size_t current_location_;
    GameState& game_;

 public:
    GameMapImpl(GameState& game) : game_(game) {}

    Storage<Location>& locations() override {
        return locations_;
    }

    void switchLocation(size_t id);

    void switchLocation(size_t char_id, size_t id);

    Location& currentLocation() {
        return locations_.get(current_location_);
    }

    size_t currentLocationId() const {
        return current_location_;
    }

    Storage<PlayerCharacter>& players();
};
