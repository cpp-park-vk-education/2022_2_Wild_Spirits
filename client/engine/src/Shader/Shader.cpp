#include "Shader.h"

namespace LM {

    Shader::Shader(const ShaderLayout& layout)
        : m_Layout(layout)
    {

    }
    
    Shader::~Shader() {

    }

    void Shader::enable() const {

    }

    void Shader::disable() const {

    }

    void Shader::setUniform1f(std::string_view name, float value) {

    }

    void Shader::setUniform1fv(std::string_view name, float* value, int count) {

    }

    void Shader::setUniform1i(std::string_view name, int value) {

    }

    void Shader::setUniform1iv(std::string_view name, int* value, int count) {

    }

    void Shader::setUniform2f(std::string_view name, const glm::vec2& vector) {

    }

    void Shader::setUniform3f(std::string_view name, const glm::vec3& vector) {

    }

    void Shader::setUniform4f(std::string_view name, const glm::vec4& vector) {

    }

    void Shader::setUniformMat4(std::string_view name, const glm::mat4& matrix) {

    }

    uint32_t Shader::load(const ShaderLayout& layout) {
        return 0;
    }

    uint32_t Shader::getType(ShaderSource::Type type) {
        return 0;
    }

    std::string Shader::getName(ShaderSource::Type type) {
        return "";
    }

    uint32_t Shader::loadShader(const ShaderLayout& layout, uint32_t sourceId) {
        return 0;
    }
    
    std::string Shader::loadFile(std::string_view filepath) {
        return "";
    }

    int Shader::getUniformLocation(std::string_view name) const
    {
        return 0;
    }

}