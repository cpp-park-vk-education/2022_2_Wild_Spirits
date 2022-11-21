#pragma once

#include "BufferLayout.h"

namespace LM {

    class VertexBuffer
    {
    public:
        VertexBuffer(uint32_t size);
        VertexBuffer(const void* data, uint32_t size);
        ~VertexBuffer();

        void bind()        const;
        void unbind()    const;

        void setData(const void* data, uint32_t size);

        const BufferLayout& getLayout() const { return m_Layout; }
        void setLayout(const BufferLayout& layout) { m_Layout = layout; }
    private:
        uint32_t m_BufferId;
        BufferLayout m_Layout;
    };

}
