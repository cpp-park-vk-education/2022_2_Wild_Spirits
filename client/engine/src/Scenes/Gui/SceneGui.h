#pragma once

#include <Core/Base.h>
#include <Renderables/Gui/RenderableGui.h>
#include <Renderers/Renderer.h>
#include <Scenes/SceneInterface.h>

namespace LM {

    class SceneGui : public SceneInterface {
    public:
        SceneGui();
        virtual ~SceneGui();

        void add(Ref<RenderableGui> renderable);
        void remove(Ref<RenderableGui> renderable);
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

}    // namespace LM
