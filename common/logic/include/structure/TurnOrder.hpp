#pragma once

#include <deque>
#include <cstddef>

#include "Utils.hpp"

class GameMap;
class GameState;
class CharacterInstance;

class TurnOrder {
 private:
    size_t current_turn_;
    std::deque<CharacterInstance*> turn_order_queue_;
    GameState& game_;
    GameMap& map_;
 
 public:
    using size_type = size_t;

    TurnOrder(GameState& game, GameMap& map) :
        current_turn_(0), turn_order_queue_(),
        game_(game), map_(map) {}
    
    void nextTurn();
    void skipTurns(size_t turns);

    ErrorStatus pushBack(size_t char_id);
    ErrorStatus pushFront(size_t char_id);

    void fillQueue();  // Pushes all players and npc's on current location to the queue

    ErrorStatus swapOrder(size_t first, size_t second);
    CharacterInstance* getActiveCharacter() const;

    auto begin() {
        return turn_order_queue_.begin();
    }

    auto end() {
        return turn_order_queue_.end();
    }

    size_t size() const {
        return turn_order_queue_.size();
    }
};
