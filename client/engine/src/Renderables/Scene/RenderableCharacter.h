#pragma once

#include <Renderables/RenderableTexture.h>

namespace LM {

    class RenderableCharacter : public RenderableTexture {
    public:
        RenderableCharacter(Ref<Texture2D> texture, const Color& color, const glm::uvec2& position);

        const glm::uvec2& getPosition() const { return m_Position; }
        void drawImGuiTooltip();
    protected:
        glm::uvec2 m_Position;
    };

}    // namespace LM
