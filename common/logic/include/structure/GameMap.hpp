#pragma once

#include "Location.hpp"

#include "PlayerCharacter.hpp"

namespace DnD {
class GameState;

class GameMap {
 public:
    virtual Storage<Location>& locations() = 0;

    virtual ErrorStatus switchLocation(size_t id) = 0;
    virtual ErrorStatus switchLocation(size_t char_id, size_t id) = 0;

    virtual Location& currentLocation() = 0;
    virtual size_t currentLocationId() const = 0;

    virtual SharedStorage<PlayerCharacter>& players() = 0;
    virtual Storage<CharacterInstance*>& allCharacters() const = 0;

    virtual ~GameMap() {}

    virtual ErrorStatus createPlayer(std::shared_ptr<PlayerCharacter> player) = 0;
};

class GameMapImpl : public GameMap {
 private:
    Storage<Location> locations_;
    GameState& game_;
    size_t current_location_;
    SharedStorage<PlayerCharacter> players_;

 public:
    GameMapImpl(GameState& game) : game_(game), current_location_(0) {}

    GameMapImpl(GameState& game, Storage<Location>&& locations,
                SharedStorage<PlayerCharacter>&& players, size_t current_id) :
        locations_(locations), game_(game),
        current_location_(current_id),
        players_(players) {}

    Storage<Location>& locations() override {
        return locations_;
    }

    ErrorStatus switchLocation(size_t id) override;

    ErrorStatus switchLocation(size_t char_id, size_t id) override;

    Location& currentLocation() override {
        return locations_.get(current_location_);
    }

    size_t currentLocationId() const override {
        return current_location_;
    }

    SharedStorage<PlayerCharacter>& players() override;
    Storage<CharacterInstance*>& allCharacters() const override;

    ErrorStatus createPlayer(std::shared_ptr<PlayerCharacter> player) override;
};
}  // namespace DnD
