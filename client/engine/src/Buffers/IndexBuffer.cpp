#include "IndexBuffer.h"

#include <GL/glew.h>

namespace LM {
    IndexBuffer::IndexBuffer(uint32_t count)
        : m_Count(count) {
        glGenBuffers(1, &m_BufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    }

    IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
        : m_Count(count) {
        glGenBuffers(1, &m_BufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_BufferId);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::setIndices(const uint32_t* data, uint32_t count) {
        m_Count = count;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Count * sizeof(uint32_t), data);
    }

}    // namespace LM
