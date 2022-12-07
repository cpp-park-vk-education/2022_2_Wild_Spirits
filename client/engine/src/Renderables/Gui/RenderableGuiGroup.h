#pragma once

#include "RenderableGui.h"
#include <Renderables/RenderableGroupInterface.h>
#include <Core/Base.h>

namespace LM {

    class RenderableGuiGroup : public RenderableGui {
    public:
        RenderableGuiGroup(Vector<Ref<RenderableGui>> renderables = {}, const RenderableGuiProps& propsGui = {});
        virtual ~RenderableGuiGroup() = default;

        virtual void add(Ref<RenderableGui> renderable) { m_Renderables.emplace_back(renderable); }
        virtual void remove(size_t id) { m_Renderables.erase(m_Renderables.begin() + id); }
        const Vector<Ref<RenderableGui>>& getRenderables() const { return m_Renderables; }

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;

        virtual void rebuid(glm::uvec2 size) override;
        virtual glm::vec2 getSize() const override;
        virtual void draw(RendererInterface* renderer) override;
    protected:
        Vector<Ref<RenderableGui>> m_Renderables;
    };

}
