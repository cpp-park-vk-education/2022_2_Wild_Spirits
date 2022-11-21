#include "TurnOrder.hpp"

#include "GameState.hpp"
#include "GameMap.hpp"

ErrorStatus TurnOrder::nextTurn() {
    return ErrorStatus::Fail;
}

ErrorStatus TurnOrder::addToQueueBack(size_t char_id) {
    return ErrorStatus::Fail;
}

ErrorStatus TurnOrder::addToQueueFront(size_t char_id) {
    return ErrorStatus::Fail;
}

ErrorStatus TurnOrder::swapTurnOrder(size_t first, size_t second) {
    return ErrorStatus::Fail;
}

size_t TurnOrder::getActiveCharacterId() {
    return 0;
}
