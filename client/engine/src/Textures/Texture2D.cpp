#include "Texture2D.h"

#include <GL/glew.h>

#include "TextureLoader.h"
#include "CalcTextureParameters.h"

namespace LM {

    Texture2D::Texture2D(FromFile file, Texture2D::MASK mask) 
        : m_Mask(mask) 
    {
        TextureLoader textureLoader(TextureLoader::FromFile(file.filename));
        if (!textureLoader.isOk())
        {
            loadOnError();
        }
        else
        {
            load(textureLoader.getData(), textureLoader.getWidht(), textureLoader.getHeight());
        }
    }

    Texture2D::Texture2D(FromSource source, Texture2D::MASK mask) 
        : m_Mask(mask) 
    {
        TextureLoader textureLoader(TextureLoader::FromSource(source.source));
        if (!textureLoader.isOk())
        {
            loadOnError();
        }
        else
        {
            load(textureLoader.getData(), textureLoader.getWidht(), textureLoader.getHeight());
        }
    }
    
    Texture2D::Texture2D(FromData data, MASK mask)
        : m_Mask(mask) 
    {
        load(data.data, data.width, data.height);
    }

    Texture2D::~Texture2D() {

    }

    void Texture2D::bind(uint32_t slotId) {
        glActiveTexture(GL_TEXTURE0 + slotId);
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
    }

    void Texture2D::unbind() {

    }

    void Texture2D::load(const uint8_t* const data, uint32_t width, uint32_t height) {
        m_Width = width;
        m_Height = height;

        //glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureId);
        glGenTextures(1, &m_TextureId);
        glBindTexture(GL_TEXTURE_2D, m_TextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, CalcTextureParameters::wrapS(m_Mask));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, CalcTextureParameters::wrapT(m_Mask));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, CalcTextureParameters::minFilter(m_Mask));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, CalcTextureParameters::magFilter(m_Mask));

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        if (CalcTextureParameters::hasMipmap(m_Mask))
        {
            glGenerateMipmap(m_TextureId);
        }
    }
    
    void Texture2D::loadOnError() {
        glGenTextures(1, &m_TextureId);
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
        m_Width = 2;
        m_Height = 2;

        uint32_t Data[] = { 0xffff00ff, 0xff000000, 0xff000000, 0xffff00ff };

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_Width, m_Height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    }

}
