#include "RenderableCharacter.h"

#include <imgui.h>

namespace LM {

    RenderableCharacter::RenderableCharacter(Ref<Texture2D> texture, const Color& color,
                                             const glm::uvec2& position)
        : RenderableTexture({ texture, glm::vec2(1.0f), { glm::vec2(position.x, position.y) }, color }),
          m_Position(position) { }

    void RenderableCharacter::drawImGuiTooltip() {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted("Character Info:");
        ImGui::EndTooltip();
    }

}    // namespace LM
