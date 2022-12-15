#include "TextureManager.h"

namespace LM {

    void TextureManager::add(size_t id, Ref<Texture2D> texture) {
        m_Textures[id] = texture;
    }

    void TextureManager::remove(size_t id) {
        (void)id;
    }

    void TextureManager::remove(Ref<Texture2D> texture) {
    }

    bool TextureManager::has(size_t id) {
        return m_Textures.contains(id);
    }

    Ref<Texture2D> TextureManager::get(size_t id) {
        return m_Textures[id];
    }

}
