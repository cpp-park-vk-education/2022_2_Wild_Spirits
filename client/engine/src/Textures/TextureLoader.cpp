#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
        m_Data = stbi_load_from_memory((stbi_uc*)source.source.data(), static_cast<int>(source.source.size()), &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);
        if (!m_Data) {
            LOGW("Can't load texture from source!");
        }
    }

    TextureLoader::~TextureLoader() {
        if (m_Data) {
            stbi_image_free(m_Data);
        }
    }

}
