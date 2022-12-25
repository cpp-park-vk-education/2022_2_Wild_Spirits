#pragma once

#include <Core/Base.h>
#include <Renderables/RenderableInterface.h>
#include <Renderers/Renderer.h>
#include <Scenes/SceneInterface.h>

namespace LM {

    class Scene : public SceneInterface {
    public:
        Scene();
        virtual ~Scene();

        void add(Ref<RenderableInterface> renderable);
        void remove(Ref<RenderableInterface> renderable);
        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
        virtual void render() override;
        virtual void clear() override;

    protected:
        Vector<Ref<RenderableInterface>> m_Renderables;
        Scope<Renderer> m_Renderer;
    };

}    // namespace LM
