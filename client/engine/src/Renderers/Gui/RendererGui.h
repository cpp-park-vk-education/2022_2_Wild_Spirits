#pragma once

#include <Renderers/Renderer.h>
#include <Transform/Transform.h>
#include <Shader/Shader.h>

namespace LM {

    class RenderableGuiTexture;
    class RenderableGuiGroup;

    class RendererGui : public Renderer {
    public:
        RendererGui();
        virtual ~RendererGui();

        void draw(RenderableGuiTexture* renderable);
        void draw(RenderableGuiGroup* renderable);
    protected:
        Vector<Transform> m_Transforms;
        Ref<Shader> m_Shader;
    };

}
