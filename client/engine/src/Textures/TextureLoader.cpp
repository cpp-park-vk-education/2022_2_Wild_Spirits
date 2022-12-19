#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#ifndef STBI_MALLOC
#define STBI_MALLOC(sz)           ((sz) ? malloc(sz) : reinterpret_cast<void*>(0))
#define STBI_REALLOC(p, newsz)    realloc(p, newsz)
#define STBI_FREE(p)              free(p)
#endif
#include <stb_image.h>

#include <Utils/ConsoleLog.h>

namespace LM {

    TextureLoader::TextureLoader(FromFile file) {
        stbi_set_flip_vertically_on_load(true);
        m_Data = stbi_load(file.filename.data(), &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);
        if (!m_Data) {
            LOGW("Can't load texture: ", file.filename);
        }
    }

    TextureLoader::TextureLoader(FromSource source) {
        stbi_set_flip_vertically_on_load(true);
        m_Data = stbi_load_from_memory(
            reinterpret_cast<stbi_uc*>(source.source.data()),
            static_cast<int>(source.source.size()),
            &m_Width,
            &m_Height,
            &m_Channels,
            STBI_rgb_alpha);
        if (!m_Data) {
            LOGW("Can't load texture from source!");
        }
    }

    TextureLoader::~TextureLoader() {
        if (m_Data) {
            stbi_image_free(m_Data);
        }
    }

}    // namespace LM
