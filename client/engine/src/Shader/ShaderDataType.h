#pragma once

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


    static uint32_t ShaderDataTypeSize(ShaderDataType _Type)
    {
        return 0;
    }

}