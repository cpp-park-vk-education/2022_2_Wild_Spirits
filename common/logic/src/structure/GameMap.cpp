#include "GameMap.hpp"

#include "GameState.hpp"

namespace DnD {
ErrorStatus GameMapImpl::switchLocation(size_t id) {
    if (!locations_.contains(id)) {
        return ErrorStatus::NO_SUCH_ITEM;
    }
    current_location_ = id;
    return ErrorStatus::OK;
}

ErrorStatus GameMapImpl::switchLocation(size_t char_id, size_t id) {
    if (!locations_.contains(id)) {
        return ErrorStatus::NO_SUCH_LOCATION;
    }

    auto npc_ptr = allCharacters().safeGet(id);
    if (npc_ptr == nullptr) {
        return ErrorStatus::NO_SUCH_CHARACTER;
    }

    auto npc_location = locations_.safeGet(npc_ptr->locationId());
    if (!npc_location) {
        return ErrorStatus::NO_SUCH_LOCATION;
    }

    auto& npc = npc_location->npc().get(char_id);
    locations_.get(id).npc().add(std::move(npc));
    npc_location->npc().remove(char_id);

    return ErrorStatus::OK;
}

Storage<CharacterInstance*>& GameMapImpl::allCharacters() const {
    return game_.allCharacters();
}

Storage<PlayerCharacter>& GameMapImpl::players() const {
    return game_.players();
}
}  // namespace DnD
