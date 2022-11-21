#pragma once

#include <Renderers/Renderer.h>
#include <Transform/Transform.h>
#include <Shader/Shader.h>

namespace LM {

    class RenderableSceneTexture;

    class RendererScene : public Renderer {
    public:
        RendererScene();
        virtual ~RendererScene();

        void draw(RenderableSceneTexture* renderable);
    protected:
        Vector<Transform> m_Transforms;
        Ref<Shader> m_Shader;
    };

}
