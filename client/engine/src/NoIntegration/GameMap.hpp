#pragma once

#include "GameState.hpp"

namespace DnD {

    class GameMap {
    public:
        virtual SharedStorage<PlayerCharacter>& players() = 0;

        virtual Location& currentLocation() = 0;
        virtual size_t currentLocationId() const = 0;
    };

    class GameMapImpl : public GameMap {
    public:
        GameMapImpl(GameState& game);
        virtual SharedStorage<DnD::PlayerCharacter>& players() override;

        virtual Location& currentLocation() override;
        size_t currentLocationId() const override { return m_CurrentLocation; }

    protected:
        Storage<Location> m_Locations;
        GameState& m_Game;
        size_t m_CurrentLocation;
        SharedStorage<PlayerCharacter> m_Players;
    };

}    // namespace DnD
