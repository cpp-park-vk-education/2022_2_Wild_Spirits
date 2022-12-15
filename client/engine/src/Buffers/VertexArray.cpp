#include "VertexArray.h"

#include <GL/glew.h>

#include <Core/Assert.h>

namespace LM {

    static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::None:   break;
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
        }

        CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_BufferId);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_BufferId);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_BufferId);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        bind();
        processVertexBuffer(vertexBuffer);
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        bind();
        indexBuffer->bind();
        m_IndexBuffer = indexBuffer;
    }

    void VertexArray::processVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) const {
        CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

        vertexBuffer->bind();

        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout) {
            switch (element.type) {
                case ShaderDataType::None: break;

                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4: {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(m_VertexBufferIndex,
                        element.getComponentCount(),
                        shaderDataTypeToOpenGLBaseType(element.type),
                        element.normalized ? GL_TRUE : GL_FALSE,
                        layout.getStride(),
                        reinterpret_cast<const void*>(element.offset));
                    if (layout.hasDivisor()) {
                        glVertexAttribDivisor(m_VertexBufferIndex, layout.getDivisor());
                    }
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool: {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribIPointer(m_VertexBufferIndex,
                        element.getComponentCount(),
                        shaderDataTypeToOpenGLBaseType(element.type),
                        layout.getStride(),
                        reinterpret_cast<const void*>(element.offset));
                    if (layout.hasDivisor()) {
                        glVertexAttribDivisor(m_VertexBufferIndex, layout.getDivisor());
                    }
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    uint32_t count = element.getComponentCount();
                    for (uint32_t i = 0; i < count; ++i) {
                        glEnableVertexAttribArray(m_VertexBufferIndex);
                        glVertexAttribPointer(m_VertexBufferIndex,
                            count,
                            shaderDataTypeToOpenGLBaseType(element.type),
                            element.normalized ? GL_TRUE : GL_FALSE,
                            layout.getStride(),
                            (const void*)(element.offset + sizeof(float) * count * i));
                        if (layout.hasDivisor()) {
                            glVertexAttribDivisor(m_VertexBufferIndex, layout.getDivisor());
                        }
                        m_VertexBufferIndex++;
                    }
                    break;
                }
            }
        }
    }

}    // namespace LM
