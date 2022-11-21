#pragma once

#include <string>

#include <Core/Base.h>
#include <Shader/ShaderDataType.h>

namespace LM {
    
    struct BufferElement {
        BufferElement() = default;

        BufferElement(ShaderDataType type, std::string_view name, bool normalized = false) 
            : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
        { }

        uint32_t getComponentCount() const {
            return 0;
        }

        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;
    };


    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& elements, uint32_t divisor = 0)
            : m_Elements(elements), m_Divisor(divisor) 
        {
            calculateOffsetsAndStride();
        }

        bool gasDivisor() const { return m_Divisor; }
        uint32_t getDivisor() const { return m_Divisor; }

        inline uint32_t getStride() const { return m_Stride; }

        inline const Vector<BufferElement>& getElements() const { return m_Elements; }

        Vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        Vector<BufferElement>::iterator end()   { return m_Elements.end(); }

        Vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        Vector<BufferElement>::const_iterator end()      const { return m_Elements.end(); }
    private:
        void calculateOffsetsAndStride() { }
    private:
        Vector<BufferElement> m_Elements;
        uint32_t m_Divisor = 0;
        uint32_t m_Stride = 0;
    };

}
