#pragma once

#include <Core/Assert.h>
#include <cstdint>

namespace LM {

    enum class ShaderDataType {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    class ShaderDataTypeFuncs {
    public:
        static uint32_t ShaderDataTypeSize(ShaderDataType _Type) {
            switch (_Type) {
                case ShaderDataType::None: break;
                case ShaderDataType::Float: return 4;
                case ShaderDataType::Float2: return 4 * 2;
                case ShaderDataType::Float3: return 4 * 3;
                case ShaderDataType::Float4: return 4 * 4;
                case ShaderDataType::Mat3: return 4 * 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4 * 4;
                case ShaderDataType::Int: return 4;
                case ShaderDataType::Int2: return 4 * 2;
                case ShaderDataType::Int3: return 4 * 3;
                case ShaderDataType::Int4: return 4 * 4;
                case ShaderDataType::Bool: return 1;
            }

            CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

}    // namespace LM
