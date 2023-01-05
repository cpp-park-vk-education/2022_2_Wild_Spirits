#pragma once

namespace DnD {

    class TurnOrder {
    public:
        TurnOrder(GameState& game, GameMap& map) : m_Game(game), m_Map(map) { }

    protected:
        GameState& m_Game;
        GameMap& m_Map;
    };

}    // namespace DnD
