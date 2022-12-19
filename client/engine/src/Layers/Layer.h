#pragma once

#include <Core/Base.h>
#include <Events/Events.h>
#include <Renderables/Gui/RenderableGui.h>
#include <Renderables/RenderableInterface.h>
#include <Scenes/Gui/SceneGui.h>
#include <Scenes/Scene/Scene.h>
#include <Utils/Timer.h>

namespace LM {

    class Layer {
    public:
        Layer();
        virtual ~Layer() = default;

        virtual void addToGui(Ref<RenderableGui> renderable) { m_SceneGui->add(renderable); }
        virtual void removeFromGui(Ref<RenderableGui> renderable) { m_SceneGui->remove(renderable); }
        virtual void addToScene(Ref<RenderableInterface> renderable) { m_SceneScene->add(renderable); }
        virtual void removeFromScene(Ref<RenderableInterface> renderable) {
            m_SceneScene->remove(renderable);
        }

        virtual void onEvent(Ref<Event> _Event);
        virtual void onUpdate(Tick tick);
        virtual void render();
        virtual void renderImGui() { }

    protected:
        Ref<Scene> m_SceneScene;
        Ref<SceneGui> m_SceneGui;
    };

}    // namespace LM
