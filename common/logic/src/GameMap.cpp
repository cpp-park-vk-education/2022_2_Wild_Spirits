#include "GameMap.hpp"

#include "GameState.hpp"

namespace DnD {
void GameMapImpl::switchLocation(size_t id) {}

void GameMapImpl::switchLocation(size_t char_id, size_t id) {}

Storage<PlayerCharacter>& GameMapImpl::players() const {
    return game_.players();
}
}  // namespace DnD
