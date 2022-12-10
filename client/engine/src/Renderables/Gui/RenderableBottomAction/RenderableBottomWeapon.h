#pragma once

#include "RenderableBottomAction.h"

namespace LM {

    class RenderableBottomWeapon : public RenderableBottomAction {
    public:
        RenderableBottomWeapon(const RenderableTextureProps& props, GS::Weapon& weapon)
            : RenderableBottomAction(props), m_Weapon(weapon) { }
        
        virtual Ref<UseAction> createUseAction(size_t actionId) const override { return CreateRef<UseAction>(m_Weapon, Action::Type::kUseWeapon, actionId); }
    protected:
        GS::Weapon& m_Weapon;
    };

}
