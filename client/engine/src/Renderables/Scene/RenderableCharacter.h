#pragma once

#include <Renderables/RenderableTexture.h>

namespace LM {

    class RenderableCharacter: public RenderableTexture {
    public:
        RenderableCharacter(Ref<Texture2D> texture, const Color& color, const glm::uvec2& position);
    protected:
        glm::uvec2 m_Position;
    };

}
