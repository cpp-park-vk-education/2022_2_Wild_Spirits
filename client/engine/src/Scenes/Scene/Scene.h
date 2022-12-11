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
        void remove(Ref<RenderableInterface> renderable) {
            if (auto it = std::find(m_Renderables.begin(), m_Renderables.end(), renderable); it != m_Renderables.end()) {
                m_Renderables.erase(it);
            }
        }
        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
        virtual void render() override;
    protected:
        Vector<Ref<RenderableInterface>> m_Renderables;
        Scope<Renderer> m_Renderer;
    };

}
