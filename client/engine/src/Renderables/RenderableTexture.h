#pragma once

#include "Renderable.h"
#include <Textures/Texture2D.h>
#include <Buffers/VertexArray.h>

namespace LM {

    struct RenderableTextureProps {
        Ref<Texture2D> texture;
        Transform transform = Transform();
        Color color = Color();
    };

    class RenderableTexture : public Renderable {
    public:
        RenderableTexture(const RenderableTextureProps& props);
        virtual ~RenderableTexture() = default;

        virtual void draw(RendererInterface* renderer) override;
        Ref<VertexArray> getVertexArray() const { return m_VertexArray; }
        Ref<Texture2D> getTexture() const { return m_Texture; }
    protected:
        Ref<VertexArray> m_VertexArray;
        Ref<Texture2D> m_Texture;
    };

}
