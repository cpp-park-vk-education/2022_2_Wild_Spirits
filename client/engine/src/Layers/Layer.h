#pragma once

#include <Core/Base.h>
#include <Events/Events.h>
#include <Scenes/Gui/SceneGui.h>
#include <Renderables/Gui/RenderableGui.h>
#include <Renderables/Scene/RenderableScene.h>
#include <Scenes/Scene/SceneScene.h>
#include <Utils/Timer.h>

namespace LM {
 
    class Layer {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void addToGui(Ref<RenderableGui> renderable) { m_SceneGui->add(renderable); }
        virtual void addToScene(Ref<RenderableScene> renderable) { m_SceneScene->add(renderable); }

        virtual void onEvent(Ref<Event> _Event) { }
        virtual void onUpdate(Tick tick) { }
        virtual void render() { }
    protected:
        Ref<SceneGui> m_SceneGui;
        Ref<SceneScene> m_SceneScene;
    };

}
