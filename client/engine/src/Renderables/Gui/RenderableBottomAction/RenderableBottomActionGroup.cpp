#include "RenderableBottomActionGroup.h"
#include <Utils/ConsoleLog.h>

namespace LM {

    RenderableBottomActionGroup::RenderableBottomActionGroup(float space, const RenderableGuiProps& propsGui) 
        : RenderableGuiGroup({ }, propsGui), m_Space(space)
    {

    }

    void RenderableBottomActionGroup::add(Ref<RenderableBottomWeapon> renderable) {
        m_Weapon.push_back(renderable);
        m_Renderables.push_back(renderable);
    }

    void RenderableBottomActionGroup::add(Ref<RenderableBottomSpell> renderable) {
        m_Spell.push_back(renderable);
        m_Renderables.push_back(renderable);
    }
    
    void RenderableBottomActionGroup::add(Ref<RenderableBottomSkill> renderable) {
        m_Skill.push_back(renderable);
        m_Renderables.push_back(renderable);
    }
    
    void RenderableBottomActionGroup::add(Ref<RenderableBottomConsumable> renderable) {
        m_Consumable.push_back(renderable);
        m_Renderables.push_back(renderable);
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
