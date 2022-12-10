#pragma once

#include "RenderableGroupInterface.h"
#include "Renderable.h"

namespace LM {

    class RenderableGroup : public RenderableGroupInterface {
    public:
        RenderableGroup(const Transform& transform = Transform()) : RenderableGroupInterface(transform) { }
        virtual ~RenderableGroup() = default;

        void add(Ref<RenderableInterface> renderable);
        void remove(size_t id);
        const Vector<Ref<RenderableInterface>>& getRenderables() const { return m_Renderables; }

        virtual Ref<RenderableInterface> getRenderable(size_t id) const override { return m_Renderables[id]; }
        virtual size_t getRenderablesCount() const override { return m_Renderables.size(); }
    protected:
        virtual Vector<Ref<RenderableInterface>> getRenderables() override { return m_Renderables; }
    protected:
        Vector<Ref<RenderableInterface>> m_Renderables;
    };

}
