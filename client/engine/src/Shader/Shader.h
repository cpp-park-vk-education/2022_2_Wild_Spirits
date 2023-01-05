#pragma once

#include <string_view>
#include <unordered_map>

#include <glm/glm.hpp>

#include "ShaderLayout.h"

namespace LM {

    class Shader {
    public:
        explicit Shader(const ShaderLayout& layout);
        ~Shader();

        void enable() const;
        static void disable();

        void setUniform1f(const std::string_view& name, float value) const;
        void setUniform1fv(const std::string_view& name, float* value, int count) const;
        void setUniform1i(const std::string_view& name, int value) const;
        void setUniform1iv(const std::string_view& name, int* value, int count) const;
        void setUniform2f(const std::string_view& name, const glm::vec2& vector) const;
        void setUniform3f(const std::string_view& name, const glm::vec3& vector) const;
        void setUniform4f(const std::string_view& name, const glm::vec4& vector) const;
        void setUniformMat4(const std::string_view& name, const glm::mat4& matrix) const;

    protected:
        static uint32_t load(const ShaderLayout& layout);
        static uint32_t getType(ShaderSource::Type type);
        static std::string getName(ShaderSource::Type type);
        static uint32_t loadShader(const ShaderLayout& layout, uint32_t sourceId);
        static std::string loadFile(std::string_view filepath);

    protected:
        int getUniformLocation(const std::string_view& name) const;

    protected:
        uint32_t m_ShaderId;
        mutable std::unordered_map<std::string, int> m_UniformLocationCache;
        ShaderLayout m_Layout;
    };

}    // namespace LM
