#pragma once

#include "RenderableBottomAction.h"

namespace LM {

    class RenderableBottomSpell : public RenderableBottomAction {
    public:
        RenderableBottomSpell(const RenderableTextureProps& props, GS::Spell& spell)
            : RenderableBottomAction(props), m_Spell(spell) { }

        virtual Ref<UseAction> createUseAction(size_t actionId) const { return CreateRef<UseAction>(m_Spell, Action::Type::kUseSpell, actionId); }
    protected:
        GS::Spell& m_Spell;
    };

}
