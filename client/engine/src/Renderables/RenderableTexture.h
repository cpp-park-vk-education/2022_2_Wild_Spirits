#pragma once

#include "Renderable.h"
#include <Textures/Texture2D.h>
#include <Buffers/VertexArray.h>

namespace LM {

    struct RenderableTextureProps {
        Ref<Texture2D> texture;
        glm::vec2 size = glm::vec2(0.0f);
        Transform transform = Transform();
        Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    };

    class RenderableTexture: public Renderable {
    public:
        RenderableTexture(const RenderableTextureProps& props);
        virtual ~RenderableTexture() = default;

        virtual void draw(RendererInterface* renderer) override;
        glm::vec2 getSize() const { return m_Size; }
        Ref<VertexArray> getVertexArray() const { return m_VertexArray; }
        Ref<Texture2D> getTexture() const { return m_Texture; }
    protected:
        Ref<VertexArray> m_VertexArray;
        Ref<Texture2D> m_Texture;
        glm::vec2 m_Size;
    };

}    // namespace LM
