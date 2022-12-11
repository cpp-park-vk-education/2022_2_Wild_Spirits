#include "RenderableTileGroup.h"

#include <Core/Application.h>

namespace LM {

    constexpr glm::vec2 winSize = glm::vec2(16.0f, 9.0f);
    constexpr float tileSize = 0.95f;
    
    RenderableTileGroup::RenderableTileGroup(Ref<Texture2D> texture, glm::uvec2 size) 
        : m_TextureTile(texture), m_Size(size)
    {
        const float winCover = 0.85f;
        const glm::vec2 availSize = winSize * winCover;

        m_Tiles.reserve(m_Size.x * m_Size.y);
        m_Renderables.reserve(m_Size.x * m_Size.y);
        m_Transform.scale = glm::vec2(glm::min(availSize.x / m_Size.x, availSize.y / m_Size.y));
        m_Transform.position = glm::vec2(winSize.x / 2.0f - m_Size.x * m_Transform.scale.x / 2.0f, winSize.y / 2 - m_Size.y * m_Transform.scale.y / 2.0f);

        for (uint32_t y = 0; y < m_Size.y; ++y) {
            for (uint32_t x = 0; x < m_Size.x; ++x) {
                Ref<RenderableTile> tile = CreateRef<RenderableTile>(RenderableTextureProps{ m_TextureTile, glm::vec2(tileSize), { glm::vec2(x, y) } });
                m_Tiles.push_back(tile);
                m_Renderables.push_back(tile);
            }
        }
        m_HoveredId = m_Tiles.size();
        m_FocusedId = m_Tiles.size();
    }

    void RenderableTileGroup::addCharacter(Ref<RenderableCharacter> renderable) {
        m_Characters.push_back(renderable);
        m_Renderables.push_back(renderable);
    }

    bool RenderableTileGroup::hasHovered() const {
        return m_HoveredId < m_Tiles.size();
    }

    size_t RenderableTileGroup::getHoveredX() const {
        return m_HoveredId % m_Size.x;
    }
    
    size_t RenderableTileGroup::getHoveredY() const {
        return m_HoveredId / m_Size.x;
    }

    void RenderableTileGroup::setHoveredInFocus() {
        if (m_HoveredId >= m_Tiles.size()) { return; }
        clearFocused();

        m_FocusedId = m_HoveredId;
        m_Tiles[m_FocusedId]->setColor(s_FocusedColor);
    }
    
    void RenderableTileGroup::clearFocused() {
        if (m_FocusedId >= m_Tiles.size()) { return; }

        m_Tiles[m_FocusedId]->setColor(m_FocusedId == m_HoveredId ? s_HoveredColor : s_DefaultColor);
        m_FocusedId = m_Tiles.size();
    }

    void RenderableTileGroup::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseMovedEvent>([&](Ref<MouseMovedEvent> e) {
            glm::vec2 cursorPos = glm::vec2(
                e->getX() / Application::get()->getWindow()->getWidth() * winSize.x,
                e->getY() / Application::get()->getWindow()->getHeight() * winSize.y);
            float startX = m_Transform.position.x;
            float endX = startX + m_Transform.scale.x;
            for (uint32_t x = 0; x < m_Size.x; ++x) {
                if (cursorPos.x >= startX && cursorPos.x <= endX) {
                    float startY = m_Transform.position.y;
                    float endY = startY + m_Transform.scale.y;
                    for (uint32_t y = 0; y < m_Size.y; ++y) {
                        if (cursorPos.y >= startY && cursorPos.y <= endY) {
                            LOGI("CP At: ", x, ", ", y);
                            changeHover(x, y);
                            return false;
                        }
                        startY += m_Transform.scale.y;
                        endY += m_Transform.scale.y;
                    }
                    break;
                }
                startX += m_Transform.scale.x;
                endX += m_Transform.scale.x;
            }

            unselectHover();
            return false;
        });
    }

    void RenderableTileGroup::onUpdate(Tick tick) {

    }

    uint32_t RenderableTileGroup::getTileIndex(uint32_t x, uint32_t y) const
    {
        return y * m_Size.x + x;
    }

    void RenderableTileGroup::unselectHover() {
        if (m_HoveredId >= m_Tiles.size()) { return; }
        
        if (m_HoveredId != m_FocusedId) {
            m_Tiles[m_HoveredId]->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
        }
        m_HoveredId = m_Tiles.size();
    }

    void RenderableTileGroup::changeHover(uint32_t x, uint32_t y) {
        unselectHover();
        m_HoveredId = getTileIndex(x, y);
        if (m_HoveredId != m_FocusedId) {
            m_Tiles[m_HoveredId]->setColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
        }
    }

}
