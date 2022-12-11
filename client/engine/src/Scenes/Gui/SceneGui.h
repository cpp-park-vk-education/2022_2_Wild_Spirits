#pragma once

#include <Core/Base.h>
#include <Scenes/SceneInterface.h>
#include <Renderables/Gui/RenderableGui.h>
#include <Renderers/Renderer.h>

namespace LM {

    class SceneGui : public SceneInterface {
    protected:
        //struct TransformData {
        //    glm::mat4 transform;
        //    glm::vec2 position;
        //    glm::vec2 size;
        //};
    public:
        SceneGui();
        virtual ~SceneGui();
        
        void add(Ref<RenderableGui> renderable) { m_Renderables.emplace_back(renderable); }
        void remove(Ref<RenderableGui> renderable) {
            if (auto it = std::find(m_Renderables.begin(), m_Renderables.end(), renderable); it != m_Renderables.end()) {
                m_Renderables.erase(it);
            }
        }
        void rebuild();

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
        virtual void render() override;
    protected:
        Vector<Ref<RenderableGui>> m_Renderables;
        Scope<Renderer> m_Renderer;

        uint32_t m_Width = 0; 
        uint32_t m_Height = 0;
    };

}
