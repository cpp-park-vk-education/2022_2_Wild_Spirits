#include "GameMap.hpp"

#include "GameState.hpp"

void GameMapImpl::removeLocation(size_t id) {}

void GameMapImpl::switchLocation(size_t id) {}

void GameMapImpl::switchLocation(size_t char_id, size_t id) {}

Storage<PlayerCharacter>& GameMapImpl::players() {
    return game_.players();
}
