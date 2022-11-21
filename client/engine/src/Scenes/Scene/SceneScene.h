#pragma once

#include <Core/Base.h>
#include <Scenes/Scene.h>
#include <Renderables/Scene/RenderableScene.h>

namespace LM {

    class SceneScene : public Scene {
    public:
        SceneScene();
        virtual ~SceneScene();

        void add(Ref<RenderableScene> renderable) { m_Renderables.emplace_back(renderable); }

        virtual void onEvent(Ref<Event> event) override;
        virtual void render() override;
    protected:
        Vector<Ref<RenderableScene>> m_Renderables;
    };

}
