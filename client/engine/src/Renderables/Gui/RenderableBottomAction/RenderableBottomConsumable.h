#pragma once

#include "RenderableBottomAction.h"

namespace LM {

    class RenderableBottomConsumable : public RenderableBottomAction {
    public:
        RenderableBottomConsumable(const RenderableTextureProps& props, GS::Consumable& consumable)
            : RenderableBottomAction(props), m_Consumable(consumable) { }

        virtual Ref<UseAction> createUseAction(size_t actionId) const { return CreateRef<UseAction>(m_Consumable, Action::Type::kUseConsumable, actionId); }
    protected:
        GS::Consumable& m_Consumable;
    };

}
