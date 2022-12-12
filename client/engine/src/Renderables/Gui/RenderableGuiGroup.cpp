#include "RenderableGuiGroup.h"

namespace LM {

    RenderableGuiGroup::RenderableGuiGroup(Vector<Ref<RenderableGui>> renderables, const RenderableGuiProps& propsGui)
        : RenderableGui(propsGui), m_Renderables(renderables)
    {

    }

    void RenderableGuiGroup::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);
        bool isMouseMovedEvent = false;
        dispatcher.dispatch<MouseMovedEvent>([&](Ref<MouseMovedEvent> e) {
            isMouseMovedEvent = true;
            for (auto& renderable : m_Renderables) {
                Ref<MouseMovedEvent> newEvent = CreateRef<MouseMovedEvent>(e->getX() - m_Position.x - m_AlignPosition.x, e->getY() - m_Position.y - m_AlignPosition.y);
                renderable->onEvent(newEvent);
            }
            return false;
        });
        if (isMouseMovedEvent) { return; }
        for (auto& renderable : m_Renderables) {
            renderable->onEvent(event);
        }
    }
    
    void RenderableGuiGroup::onUpdate(Tick tick) {
        for (auto& renderable : m_Renderables) {
            renderable->onUpdate(tick);
        }
    }

    void RenderableGuiGroup::rebuid(glm::uvec2 size) {
        RenderableGui::rebuid(size);
        for (auto& renderable : m_Renderables) {
            renderable->rebuid(getSize());
        }
    }

    glm::vec2 RenderableGuiGroup::getSize() const {
        return glm::uvec2(0, 0);
    }

    void RenderableGuiGroup::draw(RendererInterface* renderer) {
        for (auto& renderable : m_Renderables)
        {
            renderable->drawDecorator(renderer);
        }
    }

}
