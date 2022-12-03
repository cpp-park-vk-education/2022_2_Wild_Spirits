#pragma once

#include "RenderableGui.h"
#include <Renderables/RenderableGroupInterface.h>
#include <Core/Base.h>

namespace LM {

    class RenderableGuiGroup : public RenderableGui, public RenderableGroupInterface {
    public:
        RenderableGuiGroup(Vector<Ref<RenderableGui>> renderables = Vector<Ref<RenderableGui>>()) : m_Renderables(renderables) { }
        virtual ~RenderableGuiGroup() = default;

        virtual void add(Ref<RenderableGui> renderable) { m_Renderables.emplace_back(renderable); }
        virtual void remove(size_t id) { m_Renderables.erase(m_Renderables.begin() + id); }
        const Vector<Ref<RenderableGui>>& getRenderables() const { return m_Renderables; }

        virtual glm::uvec2 getSize() const override;

        virtual Ref<RenderableInterface> getRenderable(size_t id) const override { return m_Renderables[id]; }
        virtual size_t getRenderablesCount() const override { return m_Renderables.size(); }
    protected:
        Vector<Ref<RenderableGui>> m_Renderables;
    };

}
