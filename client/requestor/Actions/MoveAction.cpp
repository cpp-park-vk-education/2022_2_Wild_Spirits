#include "MoveAction.h"

namespace LM {

    MoveAction::MoveAction(size_t x, size_t y) : m_TargetX(x), m_TargetY(y) { }

    Action::Type MoveAction::getType() const {
        return Action::Type::kMove; 
    }

    uint32_t MoveAction::getTargetX() const {
        return m_TargetX; 
    }

    uint32_t MoveAction::getTargetY() const {
        return m_TargetY; 
    }

    void MoveAction::setTarget(uint32_t x, uint32_t y) {
        m_TargetX = x;
        m_TargetY = y;
    }

}
