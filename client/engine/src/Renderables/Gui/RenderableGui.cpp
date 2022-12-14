#include "RenderableGui.h"

#include <Renderers/RendererInterface.h>
#include <Utils/ConsoleLog.h>

namespace LM {

    RenderableGui::RenderableGui(const RenderableGuiProps& props)
        : m_Align(props.align),
          m_AlignPosition({ 0, 0 }),
          m_Position(props.position) { }

    void RenderableGui::rebuid(glm::uvec2 size) {
        m_AlignPosition.x = calcAlign(m_Align.horizontal, size.x, getSize().x);
        m_AlignPosition.y = calcAlign(m_Align.vertical, size.y, getSize().y);
    }

    void RenderableGui::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseMovedEvent>([&](Ref<MouseMovedEvent> e) {
            glm::vec2 start = m_Position + m_AlignPosition;
            glm::vec2 end = m_Position + m_AlignPosition + getSize();
            if (e->getX() >= start.x && e->getX() <= end.x && e->getY() >= start.y && e->getY() <= end.y) {
                m_IsHovered = true;
            } else {
                m_IsHovered = false;
            }
            return false;
        });
    }

    void RenderableGui::drawDecorator(RendererInterface* renderer) {
        renderer->pushTransform(glm::translate(
            glm::vec3(m_AlignPosition.x + m_Position.x, m_AlignPosition.y + m_Position.y, 0.0f)));
        draw(renderer);
        renderer->popTransform();
    }

    float RenderableGui::calcAlign(GuiAlign align, glm::uint winSize, float size) {
        switch (align) {
            case GuiAlign::kStart: return 0.0f;
            case GuiAlign::kCenter: return (static_cast<float>(winSize) - size) / 2.0f;
            case GuiAlign::kEnd: return static_cast<float>(winSize) - size;
        }
        return 0;
    }

}    // namespace LM
