#include "GameMap.hpp"

#include "GameState.hpp"

namespace DnD {
ErrorStatus GameMapImpl::switchLocation(size_t id) {
    if (!locations_.contains(id)) {
        return ErrorStatus::NO_SUCH_ITEM;
    }
    auto& location = locations_.get(id);

    std::vector<Tile> old_positions;
    old_positions.reserve(players().size());

    for (auto& [_, player] : players()) {
        old_positions.push_back(player->mapPosition()[0]);

        auto error_status = currentLocation().transferToOtherLocation(player.get(), &location, old_positions.back());

        if (error_status != ErrorStatus::OK) {
            auto player_it = players().begin();
            for (auto pos = old_positions.begin(); pos != old_positions.end(); ++pos) {
                location.transferToOtherLocation(player_it->second.get(), &currentLocation(), *pos);
                ++player_it;
            }
            return error_status;
        }
    }

    current_location_ = id;
    return ErrorStatus::OK;
}

ErrorStatus GameMapImpl::switchLocation(size_t char_id, size_t id) {
    if (!locations_.contains(id)) {
        return ErrorStatus::NO_SUCH_LOCATION;
    }

    auto npc_ptr = allCharacters().safeGet(char_id);
    if (!npc_ptr) {
        return ErrorStatus::NO_SUCH_CHARACTER;
    }

    auto npc_location = locations_.safeGet(npc_ptr->locationId());
    if (!npc_location) {
        return ErrorStatus::NO_SUCH_LOCATION;
    }

    auto& npc = npc_location->npc().get(char_id);

    auto status = npc_location->transferToOtherLocation(&npc, locations_.safeGet(id), npc.mapPosition()[0]);
    if (status != ErrorStatus::OK) {
        return status;
    }

    locations_.get(id).npc().add(std::move(npc));
    npc_location->npc().remove(char_id);

    return ErrorStatus::OK;
}

Storage<CharacterInstance*>& GameMapImpl::allCharacters() const {
    return game_.allCharacters();
}

SharedStorage<PlayerCharacter>& GameMapImpl::players() {
    return players_;
}

ErrorStatus GameMapImpl::createPlayer(std::shared_ptr<PlayerCharacter> player) {
    auto [_, status] = players().add(player);
    if (status != ErrorStatus::OK) {
        return status;
    }

    status = currentLocation().addObject(*player);
    // if (status != ErrorStatus::OK) {
    //     players().remove(player->id());
    //     return status;
    // }

    return ErrorStatus::OK;
}
}  // namespace DnD
