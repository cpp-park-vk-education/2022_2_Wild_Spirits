#pragma once

#include <string_view>
#include <unordered_map>

#include <glm/glm.hpp>

#include "ShaderLayout.h"

namespace LM
{

	class Shader
	{
	public:
		Shader(const ShaderLayout& layout);
		~Shader();

		void enable() const;
		void disable() const;

		void setUniform1f(std::string_view name, float value);
		void setUniform1fv(std::string_view name, float* value, int count);
		void setUniform1i(std::string_view name, int value);
		void setUniform1iv(std::string_view name, int* value, int count);
		void setUniform2f(std::string_view name, const glm::vec2& vector);
		void setUniform3f(std::string_view name, const glm::vec3& vector);
		void setUniform4f(std::string_view name, const glm::vec4& vector);
		void setUniformMat4(std::string_view name, const glm::mat4& matrix);
	protected:
		uint32_t load(const ShaderLayout& layout);
		uint32_t getType(ShaderSource::Type type);
		std::string getName(ShaderSource::Type type);
		uint32_t loadShader(const ShaderLayout& layout, uint32_t sourceId);
		std::string loadFile(std::string_view filepath);
		int getUniformLocation(std::string_view name) const;
	protected:
		uint32_t m_ShaderId;
		mutable std::unordered_map<std::string, int> m_UniformLocationCache;
		ShaderLayout m_Layout;
	};

}