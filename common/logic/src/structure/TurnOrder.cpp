#include "TurnOrder.hpp"

#include "GameState.hpp"
#include "GameMap.hpp"

namespace DnD {
void TurnOrder::nextTurn() {
    getActiveCharacter()->onTurnEnd();
    current_turn_ = (current_turn_ + 1) % queue_.size();
    getActiveCharacter()->onTurnStart();
}

void TurnOrder::skipTurns(size_t turns) {
    for (size_t i = 0; i < turns; ++i) {
        nextTurn();
    }
}

ErrorStatus TurnOrder::pushBack(size_t char_id) {
    auto character = game_.allCharacters().safeGet(char_id);
    if (character == nullptr) {
        return ErrorStatus::NO_SUCH_ITEM;
    }
    queue_.push_back(character);
    return ErrorStatus::OK;
}

ErrorStatus TurnOrder::pushFront(size_t char_id) {
    auto character = game_.allCharacters().safeGet(char_id);
    if (character == nullptr) {
        return ErrorStatus::NO_SUCH_ITEM;
    }
    queue_.push_front(character);
    return ErrorStatus::OK;
}

ErrorStatus TurnOrder::swapOrder(size_t first, size_t second) {
    if (first >= size() || second >= size()) {
        return ErrorStatus::OUT_OF_RANGE;
    }
    std::swap(queue_[first], queue_[second]);
    return ErrorStatus::OK;
}

void TurnOrder::fillQueue() {
    queue_.clear();

    for (auto& [_, player] : game_.players()) {
        queue_.push_back(player.get());
    }

    for (auto& [_, character] : map_.currentLocation().npc()) {
        queue_.push_back(character.get());
    }
}

CharacterInstance* TurnOrder::getActiveCharacter() const {
    return queue_[current_turn_];
}

size_t TurnOrder::getActiveCharacterId() const {
    return getActiveCharacter()->id();
}
}  // namespace DnD
