#include "IndexBuffer.h"

namespace LM {
    IndexBuffer::IndexBuffer(uint32_t count)
        : m_Count(count)
    {

    }

    IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count) 
        : m_Count(count)
    {

    }

    IndexBuffer::~IndexBuffer() {

    }

    void IndexBuffer::bind() const {

    }

    void IndexBuffer::unbind() const {
    
    }

    void IndexBuffer::setIndices(const uint32_t* data, uint32_t count) {
    
    }

}
