#pragma once

#include <deque>
#include <memory>
#include <cstddef>

#include "ErrorStatus.hpp"

namespace DnD {
class GameMap;
class GameState;
class CharacterInstance;

class TurnOrder {
 private:
    size_t current_turn_;
    std::deque<std::weak_ptr<CharacterInstance>> queue_;
    GameState& game_;
    GameMap& map_;

    std::shared_ptr<CharacterInstance> getCharacter(size_t id);
 
 public:
    using size_type = size_t;
    using iterator = typename decltype(queue_)::iterator;

    TurnOrder(GameState& game, GameMap& map) :
        current_turn_(0), queue_(),
        game_(game), map_(map) {}
    
    void nextTurn();
    void skipTurns(size_t turns);

    ErrorStatus pushBack(size_t char_id);
    ErrorStatus pushFront(size_t char_id);

    void fillQueue();  // Pushes all players and npc's on current location to the queue

    ErrorStatus swapOrder(size_t first, size_t second);
    std::weak_ptr<CharacterInstance> getActiveCharacter() const;
    size_t getActiveCharacterId() const;

    auto begin() {
        return queue_.begin();
    }

    auto end() {
        return queue_.end();
    }

    size_t size() const {
        return queue_.size();
    }
};
} // namespace DnD
