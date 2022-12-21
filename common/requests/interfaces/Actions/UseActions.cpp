#include "UseActions.h"

namespace LM {

    UseAction::UseAction(DnD::Activatable& activatable, Type type) 
        : m_Activatable(activatable), m_Type(type)
    {

    }

    Action::Type UseAction::getType() const { 
        return m_Type;
    }

    size_t UseAction::getTargetX() const { 
        return m_TargetX; 
    }

    size_t UseAction::getTargetY() const { 
        return m_TargetY; 
    }

    void UseAction::setTarget(size_t x, size_t y) { 
        m_TargetX = x; 
        m_TargetY = y;
        m_IsFirstSet = false;
    }

    bool UseAction::isFirstSet() const {
        return m_IsFirstSet;
    }

    DnD::Activatable& UseAction::getActivatable() {
        return m_Activatable; 
    }

    std::vector<DnD::Action::Target> UseAction::getTargetTypes() const {
        return std::vector<DnD::Action::Target>();
    }
    
    DnD::Activatable::Cast UseAction::getCastType() const { 
        return m_Activatable.castType(); 
    }
    
}
