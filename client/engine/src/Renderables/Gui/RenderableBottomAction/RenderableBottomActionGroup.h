#pragma once

#include <Renderables/Gui/RenderableGuiGroup.h>
#include "RenderableBottomWeapon.h"
#include "RenderableBottomSkill.h"
#include "RenderableBottomSpell.h"
#include "RenderableBottomConsumable.h"

namespace LM {

    class RenderableBottomActionGroup : public RenderableGuiGroup {
    public:
        RenderableBottomActionGroup(float space = 5.0f, const RenderableGuiProps& propsGui = { { RenderableGuiAlign::Align::kCenter } });

        virtual void add(Ref<RenderableBottomWeapon> renderable);
        virtual void add(Ref<RenderableBottomSpell> renderable);
        virtual void add(Ref<RenderableBottomSkill> renderable);
        virtual void add(Ref<RenderableBottomConsumable> renderable);

        virtual void rebuid(glm::uvec2 size) override;
        virtual glm::vec2 getSize() const override;
    protected:
        float m_Space;

        Vector<Ref<RenderableBottomWeapon>> m_Weapon;
        Vector<Ref<RenderableBottomSpell>> m_Spell;
        Vector<Ref<RenderableBottomSkill>> m_Skill;
        Vector<Ref<RenderableBottomConsumable>> m_Consumable;
    };

}
