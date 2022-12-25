#include "GameMap.hpp"

namespace DnD {

    GameMapImpl::GameMapImpl(GameState& game) : m_Game(game), m_CurrentLocation(0) {
        m_Locations.add(0, Location(0, 10, 10));
        m_Locations.add(1, Location(1, 16, 8));
        m_Locations.add(2, Location(2, 8, 16));
        m_Players.add(0, std::make_shared<PlayerCharacter>(1, 2, TestImages::getRandomPlayerId()));
        m_Players.add(1, std::make_shared<PlayerCharacter>(1, 3, TestImages::getRandomPlayerId()));
        m_Players.add(2, std::make_shared<PlayerCharacter>(3, 2, TestImages::getRandomPlayerId()));
        m_Players.add(3, std::make_shared<PlayerCharacter>(5, 3, TestImages::getRandomPlayerId()));
    }

    SharedStorage<PlayerCharacter>& GameMapImpl::players() { return m_Players; }

    Location& GameMapImpl::currentLocation() { return m_Locations.get(m_CurrentLocation); }

}    // namespace DnD