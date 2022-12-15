#pragma once

#include <Utils/DataLoading.h>

namespace LM {

    class TextureLoader {
    public:
        explicit TextureLoader(FromFile file);
        explicit TextureLoader(FromSource source);
        ~TextureLoader();

        inline uint32_t getWidht() const { return m_Width; }
        inline uint32_t getHeight() const { return m_Height; }
        inline uint32_t geChannels() const { return m_Channels; }
        inline const uint8_t* const getData() const { return m_Data; }

        bool isOk() const { return m_Data; }
    protected:
        int m_Width;
        int m_Height;
        int m_Channels;
        uint8_t* m_Data;
    };

}    // namespace LM
