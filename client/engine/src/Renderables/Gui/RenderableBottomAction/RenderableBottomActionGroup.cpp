#include "RenderableBottomActionGroup.h"

#include <numeric>

#include <Utils/ConsoleLog.h>

namespace LM {

    RenderableBottomActionGroup::RenderableBottomActionGroup(float space, const RenderableGuiProps& propsGui)
        : RenderableGuiGroup({ }, propsGui), m_Space(space) {
    }

    void RenderableBottomActionGroup::add(Ref<RenderableBottomAction> renderable) {
        m_Items.push_back(renderable);
        m_Renderables.push_back(renderable);
    }

    Ref<UseAction> RenderableBottomActionGroup::getAction() {
        for (auto& item : m_Items) {
            if (item->isHovered()) {
                return item->createUseAction();
            }
        }
        return Ref<UseAction>();
    }

    void RenderableBottomActionGroup::setFocus() {
        for (auto& item : m_Items) {
            if (item->isHovered()) {
                item->setFocus(true);
                break;
            }
        }
    }

    void RenderableBottomActionGroup::setUnFocus() {
        for (auto& item : m_Items) {
            item->setFocus(false);
        }
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
        return glm::vec2(std::accumulate(
            m_Renderables.begin(),
            m_Renderables.end(),
            (m_Renderables.size() - 1) * m_Space,
            [](float left, const auto& right) {
                return left + right->getSize().x;
            }),
            0.0f);
    }

}    // namespace LM
