#include "TurnOrder.hpp"

#include "GameState.hpp"
#include "GameMap.hpp"

namespace DnD {
void TurnOrder::nextTurn() {
    auto it = queue_.begin() + current_turn_;
    if (it->expired()) {
        queue_.erase(it);
    } else {
        it->lock()->onTurnEnd();
    }

    current_turn_ = (current_turn_ + 1) % queue_.size();

    it = queue_.begin() + current_turn_;
    if (it->expired()) {
        queue_.erase(it);
    } else {
        it->lock()->onTurnStart();
    }
}

void TurnOrder::skipTurns(size_t turns) {
    for (size_t i = 0; i < turns; ++i) {
        nextTurn();
    }
}

std::shared_ptr<CharacterInstance> TurnOrder::getCharacter(size_t id) {
    std::shared_ptr<CharacterInstance> character = map_.currentLocation().npc().safeGet(id);
    if (!character) {
        character = map_.players().safeGet(id);
    }
    return character;
}

ErrorStatus TurnOrder::pushBack(size_t char_id) {
    auto character = getCharacter(char_id);

    if (!character) {
        return ErrorStatus::NO_SUCH_ITEM;
    }
    queue_.push_back(character);
    return ErrorStatus::OK;
}

ErrorStatus TurnOrder::pushFront(size_t char_id) {
    auto character = getCharacter(char_id);

    if (!character) {
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

    for (auto& [_, player] : map_.players()) {
        queue_.push_back(player);
    }

    for (auto& [_, character] : map_.currentLocation().npc()) {
        queue_.push_back(character);
    }
}

std::weak_ptr<CharacterInstance> TurnOrder::getActiveCharacter() const {
    return queue_[current_turn_];
}

size_t TurnOrder::getActiveCharacterId() const {
    return getActiveCharacter().lock()->id();
}
}  // namespace DnD
