#pragma once

#include <glm/gtx/transform.hpp>

#include <Events/Events.h>
#include <Utils/Timer.h>
#include "RenderableGuiAlign.h"

namespace LM {

    class RendererInterface;

    struct RenderableGuiProps {
        RenderableGuiAlign align = RenderableGuiAlign();
        glm::vec2 position = glm::vec2(0.0f, 0.0f);
    };

    class RenderableGui {
    public:
        RenderableGui(const RenderableGuiProps& props = {});
        virtual ~RenderableGui() = default;

        RenderableGuiAlign getAlight() const { return m_Align; }
        void setAlight(RenderableGuiAlign align) { m_Align = align; }

        glm::vec2 getPosition() const { return m_Position; }
        void setPosition(const glm::vec2& position) { m_Position = position; }

        virtual void rebuid(glm::uvec2 size);

        virtual void onEvent(Ref<Event> event);
        virtual void onUpdate(Tick tick) { (void)tick; }

        virtual void drawDecorator(RendererInterface* renderer);

        virtual void draw(RendererInterface* renderer) = 0;
        virtual glm::vec2 getSize() const = 0;

        bool isHovered() const { return m_IsHovered; }
        void setHovered(bool isHovered) { m_IsHovered = isHovered; }
    protected:
        float calcAlign(GuiAlign align, glm::uint winSize, float size) const;
    protected:
        RenderableGuiAlign m_Align;
        glm::vec2 m_AlignPosition;
        glm::vec2 m_Position;

        bool m_IsHovered = false;
    };

}    // namespace LM
