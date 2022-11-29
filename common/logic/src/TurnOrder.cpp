#include "TurnOrder.hpp"

#include "GameState.hpp"
#include "GameMap.hpp"

void TurnOrder::nextTurn() {}

void TurnOrder::skipTurns(size_t turns) {}

ErrorStatus TurnOrder::pushBack(size_t char_id) {
    return ErrorStatus::Fail();
}

ErrorStatus TurnOrder::pushFront(size_t char_id) {
    return ErrorStatus::Fail();
}

ErrorStatus TurnOrder::swapOrder(size_t first, size_t second) {
    return ErrorStatus::Fail();
}

void TurnOrder::fillQueue() {}

CharacterInstance* TurnOrder::getActiveCharacter() const {
    return 0;
}
