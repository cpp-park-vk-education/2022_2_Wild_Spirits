#include "RenderableTexture.h"

#include <Renderers/RendererInterface.h>

namespace LM {

    RenderableTexture::RenderableTexture(const RenderableTextureProps& props)
        : Renderable(props.transform, props.color), m_Texture(props.texture), m_Size(props.size)
    {
        if (props.size.x == 0.0f || props.size.y == 0.0f)
        {
            m_Size = m_Texture->getSize();
        }
        BufferLayout verticesLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" } });

        
        std::vector<Renderable::Vertex> vertices {
            { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(0.0f, m_Size.y, 0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(m_Size.x, m_Size.y, 0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(m_Size.x, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) }
        };

        Ref<VertexBuffer> verticesVBO = CreateRef<VertexBuffer>(vertices.data(), sizeof(vertices[0]) * vertices.size());
        verticesVBO->setLayout(verticesLayout);

        std::vector<uint32_t> indices = { 0, 1, 2, 0, 2, 3 };
        Ref<IndexBuffer> IBO = CreateRef<IndexBuffer>(indices.data(), indices.size());
        m_VertexArray = CreateRef<VertexArray>();
        m_VertexArray->addVertexBuffer(verticesVBO);
        m_VertexArray->setIndexBuffer(IBO);

    }

    void RenderableTexture::draw(RendererInterface* renderer) {
        renderer->draw(this);
    }

}
