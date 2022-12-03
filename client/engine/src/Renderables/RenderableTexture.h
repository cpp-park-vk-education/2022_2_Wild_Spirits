#pragma once

#include "Renderable.h"
#include <Textures/Texture2D.h>
#include <Buffers/VertexArray.h>

namespace LM {

    class RenderableTexture : public Renderable {
    public:
        RenderableTexture(Ref<Texture2D> texture, Transform transform = Transform(), Color color = Color());
        virtual ~RenderableTexture() = default;

        virtual void draw(RendererInterface* renderer) override;
        Ref<VertexArray> getVertexArray() const { return m_VertexArray; }
        Ref<IndexBuffer> getIndexBuffer() const { return m_IndexBuffer; }
    protected:
        Ref<VertexArray> m_VertexArray;
        Ref<IndexBuffer> m_IndexBuffer;
        Ref<Texture2D> m_Texture;
    };

}
