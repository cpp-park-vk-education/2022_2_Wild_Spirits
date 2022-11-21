#pragma once

#include <Core/Base.h>
#include <Scenes/Scene.h>
#include <Renderables/Gui/RenderableGui.h>

namespace LM {

    class SceneGui : public Scene {
    public:
        SceneGui();
        virtual ~SceneGui();
        
        void add(Ref<RenderableGui> renderable) { m_Renderables.emplace_back(renderable); }
        
        void rebuild();

        virtual void onEvent(Ref<Event> event) override;
        virtual void render() override;
    protected:
        Vector<Ref<RenderableGui>> m_Renderables;
    };

}
