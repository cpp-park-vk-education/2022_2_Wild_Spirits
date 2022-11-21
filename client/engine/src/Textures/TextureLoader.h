#pragma once

#include <string>

namespace LM {

    class TextureLoader {
    public:
        struct FromFile { std::string filename; };
        struct FromSource { std::string source; };
    public:
        TextureLoader(TextureLoader::FromFile file);
        TextureLoader(TextureLoader::FromSource source);
        ~TextureLoader();

        inline uint32_t getWidht() const { return m_Width; }
        inline uint32_t getHeight() const { return m_Height; }
        inline uint32_t geChannels() const { return m_Channels; }
        inline const uint8_t* const getData() const { return m_Data; }

        bool isOk() const { return m_Data; }
    protected:
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_Channels;
        uint8_t* m_Data;
    };

}
