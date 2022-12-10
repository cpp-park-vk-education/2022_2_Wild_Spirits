#pragma once

#include "RenderableBottomAction.h"

namespace LM {

    class RenderableBottomSkill : public RenderableBottomAction {
    public:
        RenderableBottomSkill(const RenderableTextureProps& props, GS::Skill& skill)
            : RenderableBottomAction(props), m_Skill(skill) { }

        virtual Ref<UseAction> createUseAction(size_t actionId) const { return CreateRef<UseAction>(m_Skill, Action::Type::kUseSkill, actionId); }
    protected:
        GS::Skill& m_Skill;
    };

}
