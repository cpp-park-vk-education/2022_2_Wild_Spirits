#pragma once

#include <Actions/UseActions.h>
#include <Renderables/Gui/RenderableGuiTexture.h>

namespace LM {

    class RenderableBottomAction : public RenderableGuiTexture {
    public:
        RenderableBottomAction(const RenderableTextureProps& props, const DnD::Weapon& item);
        RenderableBottomAction(const RenderableTextureProps& props, const DnD::Spell& item);
        RenderableBottomAction(const RenderableTextureProps& props, const DnD::Skill_Instance& item);
        RenderableBottomAction(const RenderableTextureProps& props, const DnD::Consumable& item);

        virtual Ref<UseAction> createUseAction() const;

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;

        void setFocus(bool focus) { m_IsFocused = focus; }
        bool isFocused() const { return m_IsFocused; }

    protected:
        const DnD::ActivatableInterface& m_Activatable;
        const Action::Type m_Type;

        bool m_IsFocused = false;
    };

}    // namespace LM
