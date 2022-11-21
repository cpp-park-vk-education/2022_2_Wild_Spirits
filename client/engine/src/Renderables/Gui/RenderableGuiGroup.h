#pragma once

#include <Core/Base.h>
#include "RenderableGui.h"

namespace LM {

    class RenderableGuiGroup : public RenderableGui {
    public:
        RenderableGuiGroup(Vector<Ref<RenderableGui>> renderables) : m_Renderables(renderables) { }
        virtual ~RenderableGuiGroup() = default;

        virtual void add(Ref<RenderableGui> renderable) { m_Renderables.emplace_back(renderable); }
        virtual void remove(size_t id) { m_Renderables.erase(m_Renderables.begin() + id); }
        const Vector<Ref<RenderableGui>>& getRenderables() const { return m_Renderables; }

        virtual void draw(RendererGui* renderer) override;
        virtual glm::uvec2 getSize() const override;
    protected:
        Vector<Ref<RenderableGui>> m_Renderables;
    };

}
