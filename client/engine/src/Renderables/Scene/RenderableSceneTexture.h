#pragma once

#include "RenderableScene.h"
#include <Textures/Texture2D.h>
#include <Buffers/VertexArray.h>

namespace LM {

    class RenderableSceneTexture : public RenderableScene {
    public:
        RenderableSceneTexture(Ref<Texture2D> texture);
        virtual ~RenderableSceneTexture() = default;

        virtual void draw(RendererScene* renderer) override;
    protected:
        Ref<VertexArray> m_VertexArray;
        Ref<Texture2D> m_Texture;
    };

}
