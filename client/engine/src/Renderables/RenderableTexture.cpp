#include "RenderableTexture.h"

#include <Renderers/RendererInterface.h>

namespace LM {

    RenderableTexture::RenderableTexture(Ref<Texture2D> texture, Transform transform, Color color)
        : Renderable(transform, color), m_Texture(texture) 
    {
        BufferLayout verticesLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" } });

        std::vector<Renderable::Vertex> vertices {
            { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) }
        };

        Ref<VertexBuffer> verticesVBO = CreateRef<VertexBuffer>(vertices.data(), sizeof(vertices[0]) * vertices.size());
        verticesVBO->setLayout(verticesLayout);

        std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };
        m_IndexBuffer = CreateRef<IndexBuffer>(indices.data(), indices.size());
        m_VertexArray = CreateRef<VertexArray>();
        m_VertexArray->addVertexBuffer(verticesVBO);
        m_VertexArray->setIndexBuffer(m_IndexBuffer);

    }

    void RenderableTexture::draw(RendererInterface* renderer) {
        renderer->draw(this);
    }

}
