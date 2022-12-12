#include "MoveAction.h"

namespace LM {

    MoveAction::MoveAction(size_t x, size_t y) : m_TargetX(x), m_TargetY(y) { }

    Action::Type MoveAction::getType() const {
        return Action::Type::kMove; 
    }

    size_t MoveAction::getTargetX() const {
        return m_TargetX; 
    }

    size_t MoveAction::getTargetY() const {
        return m_TargetY; 
    }

    void MoveAction::setTarget(size_t x, size_t y) {
        m_TargetX = x;
        m_TargetY = y;
    }

}
