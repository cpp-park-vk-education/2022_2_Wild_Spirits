#include "RenderableBottomAction.h"

namespace LM {

    RenderableBottomAction::RenderableBottomAction(const RenderableTextureProps& props, DnD::Weapon& item)
        : RenderableGuiTexture(props),
          m_Activatable(item),
          m_Type(Action::Type::kUseWeapon) { }

    RenderableBottomAction::RenderableBottomAction(const RenderableTextureProps& props, DnD::Spell& item)
        : RenderableGuiTexture(props),
          m_Activatable(item),
          m_Type(Action::Type::kUseSpell) { }

    RenderableBottomAction::RenderableBottomAction(const RenderableTextureProps& props, DnD::Skill& item)
        : RenderableGuiTexture(props),
          m_Activatable(item),
          m_Type(Action::Type::kUseSkill) { }

    RenderableBottomAction::RenderableBottomAction(const RenderableTextureProps& props, DnD::Consumable& item)
        : RenderableGuiTexture(props),
          m_Activatable(item),
          m_Type(Action::Type::kUseConsumable) { }

    Ref<UseAction> RenderableBottomAction::createUseAction() const {
        return CreateRef<UseAction>(m_Activatable, m_Type);
    }

    void RenderableBottomAction::onEvent(Ref<Event> event) { RenderableGuiTexture::onEvent(event); }

    void RenderableBottomAction::onUpdate(Tick tick) {
        RenderableGuiTexture::onUpdate(tick);
        if (m_IsFocused) {
            m_Renderable->setColor(Color(0.4f, 0.4f, 0.4f, 1.0f));
            return;
        }
        if (m_IsHovered) {
            m_Renderable->setColor(Color(0.8f, 0.8f, 0.8f, 1.0f));
        } else {
            m_Renderable->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

}    // namespace LM
