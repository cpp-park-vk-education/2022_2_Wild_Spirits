#pragma once

#include <Core/Base.h>
#include <Scenes/SceneInterface.h>
#include <Renderables/RenderableInterface.h>
#include <Renderers/Renderer.h>

namespace LM {

    class Scene : public SceneInterface {
    public:
        Scene();
        virtual ~Scene();

        void add(Ref<RenderableInterface> renderable) { m_Renderables.emplace_back(renderable); }

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
        virtual void render() override;
    protected:
        Vector<Ref<RenderableInterface>> m_Renderables;
        Scope<Renderer> m_Renderer;
    };

}
