#include "RenderableBottomActionGroup.h"
#include <Utils/ConsoleLog.h>

namespace LM {

    RenderableBottomActionGroup::RenderableBottomActionGroup(float space, Vector<Ref<RenderableGui>> renderables, const RenderableGuiProps& propsGui) 
        : RenderableGuiGroup(renderables, propsGui), m_Space(space)
    {

    }

    void RenderableBottomActionGroup::rebuid(glm::uvec2 size) {
        RenderableGui::rebuid(size);
        float offsetX = 0.0f;
        for (auto& renderable : m_Renderables) {
            renderable->setPosition(glm::vec2(offsetX, 0.0f));
            offsetX += renderable->getSize().x + m_Space;
        }
    }


    glm::vec2 RenderableBottomActionGroup::getSize() const {
        float sizeX = (m_Renderables.size() - 1) * m_Space;
        for (const auto& renderable : m_Renderables)
        {
            sizeX += renderable->getSize().x;
        }
        return glm::vec2(sizeX, 0);
    }


}
