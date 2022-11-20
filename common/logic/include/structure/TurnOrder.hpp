#pragma once

#include <deque>
#include <cstddef>

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
    
    void nextTurn();

    void addToQueueBack(size_t char_id);

    void addToQueueFront(size_t char_id);

    void swapTurnOrder(size_t first, size_t second);
    size_t getActiveCharacterId();
};
