#include "TextureManager.h"

#include <algorithm>

namespace LM {

    void TextureManager::add(size_t id, Ref<Texture2D> texture) { m_Textures[id] = texture; }

    void TextureManager::remove(size_t id) {
        if (auto it = m_Textures.find(id); it != m_Textures.end()) {
            m_Textures.erase(it);
        }
    }

    bool TextureManager::has(size_t id) { return m_Textures.contains(id); }

    Ref<Texture2D> TextureManager::get(size_t id) { return m_Textures[id]; }

}    // namespace LM
