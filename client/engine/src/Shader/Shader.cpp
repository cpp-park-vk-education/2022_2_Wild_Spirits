#include "Shader.h"

#include <fstream>

#include <GL/glew.h>

#include <Utils/ConsoleLog.h>

namespace LM {

    Shader::Shader(const ShaderLayout& layout)
        : m_Layout(layout)
    {
        m_ShaderId = load(layout);
    }
    
    Shader::~Shader() {
        glDeleteProgram(m_ShaderId);
    }

    void Shader::enable() const {
        glUseProgram(m_ShaderId);
    }

    void Shader::disable() const {
        glUseProgram(0);
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
        glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
    }

    void Shader::setUniformMat4(std::string_view name, const glm::mat4& matrix) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    uint32_t Shader::load(const ShaderLayout& layout) {
        uint32_t program = glCreateProgram();
        std::vector<uint32_t> shaders;
        for (uint32_t i = 0; i < layout.getSources().size(); ++i)
        {
            shaders.emplace_back(loadShader(layout, i));
        }

        for (uint32_t shaderId : shaders)
        {
            glAttachShader(program, shaderId);
        }

        glLinkProgram(program);
        glValidateProgram(program);

        int compileRes;
        glGetProgramiv(program, GL_LINK_STATUS, &compileRes);
        if (compileRes == GL_FALSE) {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length + 1024);
            glGetProgramInfoLog(program, length, &length, &error[0]);
            LOGE("Failed to link program!\n    ", &error[0]);
            glDeleteProgram(program);
            return 0;
        }

        for (uint32_t shaderId : shaders)
        {
            glDeleteShader(shaderId);
        }

        return program;
    }

    uint32_t Shader::getType(ShaderSource::Type type) {
        switch (type)
        {
            case ShaderSource::Type::kVertex:	return GL_VERTEX_SHADER;
            case ShaderSource::Type::kFragment:	return GL_FRAGMENT_SHADER;
            case ShaderSource::Type::kGeometry:	return GL_GEOMETRY_SHADER;
        }
        return 0;
    }

    std::string Shader::getName(ShaderSource::Type type) {
        switch (type)
        {
        case ShaderSource::Type::kVertex:	return "Vertex";
        case ShaderSource::Type::kFragment:	return "Fragment";
        case ShaderSource::Type::kGeometry:	return "Geometry";
        }
        return "None";
    }

    uint32_t Shader::loadShader(const ShaderLayout& layout, uint32_t sourceId) {
        const ShaderSource& source = layout.getSource(sourceId);
        uint32_t type = getType(source.getType());
        std::string name = getName(source.getType());

        std::string sourceString = (source.getLoadType() == ShaderSource::LoadType::kFilepath ? loadFile(source.getSource()) : source.getSource());
        const char* charSource = sourceString.c_str();
        uint32_t res = glCreateShader(type);
        glShaderSource(res, 1, &charSource, NULL);
        glCompileShader(res);

        LOGI(name, " shader code: \n", sourceString);

        int compileRes;
        glGetShaderiv(res, GL_COMPILE_STATUS, &compileRes);
        if (compileRes == GL_FALSE) {
            GLint length;
            glGetShaderiv(res, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length + 1024);
            glGetShaderInfoLog(res, length, &length, &error[0]);
            LOGE("Failed to compile ", name, " shader!\n    ", &error[0]);
            glDeleteShader(res);
            return 0;
        }

        return res;
    }
    
    std::string Shader::loadFile(std::string_view filepath) {
        std::ifstream ifStream(filepath.data());
        if (!ifStream.is_open())
            LOGE("Can't Open Shader file: ", filepath);
        std::string line;
        std::string shader;

        while (getline(ifStream, line))
        {
            shader += line + "\n";
        }

        return shader;
    }

    int Shader::getUniformLocation(std::string_view name) const
    {
        if (m_UniformLocationCache.find(name.data()) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name.data()];

        GLint location = glGetUniformLocation(m_ShaderId, name.data());
        m_UniformLocationCache[name.data()] = location;
        return location;
    }

}