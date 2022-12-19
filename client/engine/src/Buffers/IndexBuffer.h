#pragma once

#include <Core/Base.h>

namespace LM {

    class IndexBuffer {
    public:
        explicit IndexBuffer(uint32_t count);
        IndexBuffer(const uint32_t* data, uint32_t count);
        ~IndexBuffer();

        void bind() const;
        static void unbind();

        void setIndices(const uint32_t* data, uint32_t count);

        inline uint32_t getCount() const { return m_Count; }

    private:
        uint32_t m_BufferId;
        uint32_t m_Count;
    };

}    // namespace LM
