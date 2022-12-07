#include "GameMap.hpp"

#include "GameState.hpp"

namespace DnD {
void GameMapImpl::switchLocation(size_t id) {}

void GameMapImpl::switchLocation(size_t char_id, size_t id) {}

Storage<CharacterInstance*>& GameMapImpl::allCharacters() const {
    return game_.allCharacters();
}

Storage<PlayerCharacter>& GameMapImpl::players() const {
    return game_.players();
}
}  // namespace DnD
