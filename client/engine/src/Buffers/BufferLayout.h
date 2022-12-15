#pragma once

#include <string>

#include <Core/Base.h>
#include <Core/Assert.h>
#include <Shader/ShaderDataType.h>

namespace LM {

    struct BufferElement {
        BufferElement() = default;

        BufferElement(ShaderDataType type, const std::string_view& name, bool normalized = false)
            : name(name),
            type(type),
            size(ShaderDataTypeFuncs::ShaderDataTypeSize(type)),
            offset(0),
            normalized(normalized) {
        }

        uint32_t getComponentCount() const {
            switch (type) {
                case ShaderDataType::None:   break;
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3;
                case ShaderDataType::Mat4:   return 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
            }

            CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }

        std::string name;
        ShaderDataType type;
        uint32_t size;
        size_t offset;
        bool normalized;
    };


    class BufferLayout
    {
    public:
        BufferLayout() = default;

        explicit BufferLayout(const std::initializer_list<BufferElement>& elements, uint32_t divisor = 0)
            : m_Elements(elements), m_Divisor(divisor) {
            calculateOffsetsAndStride();
        }

        bool hasDivisor() const { return m_Divisor; }
        uint32_t getDivisor() const { return m_Divisor; }

        inline uint32_t getStride() const { return m_Stride; }

        inline const Vector<BufferElement>& getElements() const { return m_Elements; }

        Vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        Vector<BufferElement>::iterator end() { return m_Elements.end(); }

        Vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        Vector<BufferElement>::const_iterator end()      const { return m_Elements.end(); }
    private:
        void calculateOffsetsAndStride() {
            size_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.offset = offset;
                offset += element.size;
                m_Stride += element.size;
            }
        }
    private:
        Vector<BufferElement> m_Elements;
        uint32_t m_Divisor = 0;
        uint32_t m_Stride = 0;
    };

}    // namespace LM
