#pragma once

#include <unordered_map>

#include "Texture2D.h"

namespace LM {

    class TextureManager {
    public:
        void add(size_t id, Ref<Texture2D> texture);
        void remove(size_t id);
        bool has(size_t id);
        Ref<Texture2D> get(size_t id);
        const std::unordered_map<size_t, Ref<Texture2D>> getData() const { return m_Textures; }

    protected:
        std::unordered_map<size_t, Ref<Texture2D>> m_Textures;
    };

}    // namespace LM
