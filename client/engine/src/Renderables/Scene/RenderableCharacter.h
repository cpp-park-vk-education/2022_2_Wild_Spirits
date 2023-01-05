#pragma once

#include <GameState.hpp>
#include <Renderables/RenderableTexture.h>

namespace LM {

    class RenderableCharacter : public RenderableTexture {
    public:
        RenderableCharacter(Ref<Texture2D> texture, const glm::uvec2& position,
                            std::shared_ptr<DnD::CharacterInstance> character);

        const glm::uvec2& getPosition() const { return m_Position; }
        void drawImGuiTooltip();

    protected:
        glm::uvec2 m_Position;
        std::shared_ptr<DnD::CharacterInstance> m_Character;
    };

}    // namespace LM
