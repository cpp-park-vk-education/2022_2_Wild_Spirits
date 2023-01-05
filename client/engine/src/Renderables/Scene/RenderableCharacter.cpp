#include "RenderableCharacter.h"

#include <imgui.h>

namespace LM {

    RenderableCharacter::RenderableCharacter(Ref<Texture2D> texture, const glm::uvec2& position,
                                             std::shared_ptr<DnD::CharacterInstance> character)
        : RenderableTexture({ texture, glm::vec2(1.0f), { glm::vec2(position.x, position.y) } }),
          m_Position(position),
          m_Character(character) { }

    void RenderableCharacter::drawImGuiTooltip() {
        ImGui::BeginTooltip();
        ImGui::Text("HP: %d/%u", m_Character->hp(), m_Character->maxHP());
        ImGui::Text("CP: %u/%u", m_Character->actionPoints(), m_Character->maxActionPoints());
        ImGui::EndTooltip();
    }

}    // namespace LM
