#include "RenderableBottomAction.h"

namespace LM {

    RenderableBottomAction::RenderableBottomAction(const RenderableTextureProps& props) 
        : RenderableGuiTexture(props)
    {

    }

    void RenderableBottomAction::onEvent(Ref<Event> event) {
        RenderableGuiTexture::onEvent(event);
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>([&](Ref<MouseButtonPressedEvent> event) {
            if (m_IsHovered) {
                //m_Renderable->setColor(Color(0.1f, 0.1f, 0.1f, 1.0f));
            }
            return false;
        });
    }
    
    void RenderableBottomAction::onUpdate(Tick tick) {
        RenderableGuiTexture::onUpdate(tick);
        if (m_IsHovered) {
            m_Renderable->setColor(Color(0.5f, 0.5f, 0.5f, 1.0f));
        }
        else {
            m_Renderable->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

}
