#pragma once

#include <string>

#include <Core/Base.h>
#include "ShaderDataType.h"

namespace LM {

	class ShaderSource {
	public:
		enum class Type {
			VERTEX,
			FRAGMENT,
			GEOMETRY
		};

		enum class LoadType {
			FILEPATH,
			SOURCE
		};

		ShaderSource(Type type, std::pair<std::string, LoadType> source)
			: m_Type(type), m_LoadType(source.second), m_Source(source.first) { }

		inline Type getType()					const { return m_Type; }
		inline LoadType getLoadType()			const { return m_LoadType; }
		inline const std::string& getSource()	const { return m_Source; }
	public:
		static std::pair<std::string, LoadType> fromSource(std::string_view source) { return { source.data(), LoadType::SOURCE }; }
		static std::pair<std::string, LoadType> fromFile(std::string_view file) { return { file.data(), LoadType::FILEPATH }; }
	protected:
		Type m_Type;
		LoadType m_LoadType;
		std::string m_Source;
	};

	class ShaderLayout
	{
	public:
		ShaderLayout() = default;
		ShaderLayout(const std::initializer_list<ShaderSource>& sources);

		inline const std::vector<ShaderSource>& getSources() const { return m_Sources; }
		inline const ShaderSource& getSource(uint32_t sourceId) const { return m_Sources[sourceId]; }
	protected:
		Vector<ShaderSource> m_Sources;
	};

}