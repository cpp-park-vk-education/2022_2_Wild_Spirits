#pragma once

#include <deque>
#include <cstddef>

#include "Utils.hpp"

class GameMap;
class GameState;

class TurnOrder {
 private:
    size_t current_turn_;
    std::deque<int> turn_order_queue_;
    GameState& game_;
    GameMap& map_;
 
 public:
    TurnOrder(GameState& game, GameMap& map) :
        game_(game), map_(map) {}
    
    ErrorStatus nextTurn();

    ErrorStatus addToQueueBack(size_t char_id);

    ErrorStatus addToQueueFront(size_t char_id);

    ErrorStatus swapTurnOrder(size_t first, size_t second);
    size_t getActiveCharacterId();
};
