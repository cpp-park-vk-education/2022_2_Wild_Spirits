#include "UseActions.h"

namespace LM {

    UseAction::UseAction(GS::Activatable& activatable, Type type, size_t actionId) 
        : m_Activatable(activatable), m_Type(type), m_ActionId(actionId)
    {

    }

    Action::Type UseAction::getType() const { 
        return Type::kUseWeapon; 
    }

    uint32_t UseAction::getTargetX() const { 
        return m_TargetX; 
    }

    uint32_t UseAction::getTargetY() const { 
        return m_TargetY; 
    }

    inline void UseAction::setTarget(uint32_t x, uint32_t y) { 
        m_TargetX = x; 
        m_TargetY = y; 
    }

    GS::Activatable& UseAction::getActivatable() {
        return m_Activatable; 
    }

    GS::Action::Target UseAction::getTargetType() const {
        return m_Activatable.actions()[m_ActionId].targetType(); 
    }
    
    GS::Action::Cast UseAction::getCastType() const { 
        return m_Activatable.actions()[m_ActionId].castType(); 
    }
    
    size_t UseAction::getActionId() const { 
        return m_ActionId; 
    }

}
