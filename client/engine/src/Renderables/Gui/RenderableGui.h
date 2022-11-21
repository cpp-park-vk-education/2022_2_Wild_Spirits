#pragma once

#include <Renderables/Renderable.h>
#include "RenderableGuiAlign.h"

namespace LM {

    class RendererGui;

    class RenderableGui {
    public:
        RenderableGui() = default;
        virtual ~RenderableGui() = default;

        RenderableGuiAlight getAlight() const { return m_Align; }
        void setAlight(RenderableGuiAlight align) { m_Align = align; }

        virtual glm::uvec2 getSize() const = 0;
        virtual void draw(RendererGui* renderer) = 0;
    protected:
        RenderableGuiAlight m_Align;
    };

}
