#include "Texture2D.h"

#include "TextureLoader.h"

namespace LM {

    Texture2D::Texture2D(FromFile file, Texture2D::MASK mask) {
        m_Mask = mask;
        m_Width = 0;
        m_Height = 0;
    }

    Texture2D::Texture2D(FromSource source, Texture2D::MASK mask) {
        m_Mask = mask;
        m_Width = 100;
        m_Height = 100;
    }
    
    Texture2D::~Texture2D() {

    }

    void Texture2D::bind(uint32_t slotId) {

    }

    void Texture2D::unbind() {

    }

    void Texture2D::load() {

    }
    
    void Texture2D::loadOnError() {

    }

}
