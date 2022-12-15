#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace LM {

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        static void unbind();

        void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

        const Vector<Ref<VertexBuffer>>& getVertexBuffers() const { return m_VertexBuffers; }
        const Ref<IndexBuffer>& getIndexBuffer() const { return m_IndexBuffer; }
    private:
        void processVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) const;
    private:
        uint32_t m_BufferId;
        mutable uint32_t m_VertexBufferIndex = 0;
        Vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };

}    // namespace LM
