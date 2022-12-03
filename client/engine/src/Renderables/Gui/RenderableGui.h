#pragma once

#include <Renderables/RenderableInterface.h>
#include "RenderableGuiAlign.h"

namespace LM {

    class RenderableGui : virtual public RenderableInterface {
    public:
        RenderableGui() = default;
        virtual ~RenderableGui() = default;

        RenderableGuiAlight getAlight() const { return m_Align; }
        void setAlight(RenderableGuiAlight align) { m_Align = align; }

        virtual glm::uvec2 getSize() const = 0;
        virtual void rebuid(glm::uvec2 size) {

        };
    protected:
        RenderableGuiAlight m_Align;
    };

}
