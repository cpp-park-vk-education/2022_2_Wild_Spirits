#pragma once

#include "Location.hpp"

namespace DnD {
class GameState;
class PlayerCharacter;
class CharacterInstance;

class GameMap {
 public:
    virtual Storage<Location>& locations() = 0;

    virtual ErrorStatus switchLocation(size_t id) = 0;
    virtual ErrorStatus switchLocation(size_t char_id, size_t id) = 0;

    virtual Location& currentLocation() = 0;
    virtual size_t currentLocationId() const = 0;

    virtual Storage<PlayerCharacter>& players() const = 0;
    virtual Storage<CharacterInstance*>& allCharacters() const = 0;

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

    ErrorStatus switchLocation(size_t id) override;

    ErrorStatus switchLocation(size_t char_id, size_t id) override;

    Location& currentLocation() override {
        return locations_.get(current_location_);
    }

    size_t currentLocationId() const override{
        return current_location_;
    }

    Storage<PlayerCharacter>& players() const override;
    Storage<CharacterInstance*>& allCharacters() const override;
};
}  // namespace DnD
