#pragma once

#include "GameState.hpp"

namespace DnD {

    class GameMap {
    public:
    protected:
    };

    class GameMapImpl : public GameMap {
    public:
        GameMapImpl(GameState& game) : m_Game(game) { }

    protected:
        GameState& m_Game;
    };

}    // namespace DnD
