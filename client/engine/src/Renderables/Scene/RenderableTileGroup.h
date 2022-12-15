#pragma once

#include <Renderables/RenderableGroup.h>
#include "RenderableTile.h"
#include "RenderableCharacter.h"

namespace LM {

    class RenderableTileGroup: public RenderableGroup {
    public:
        RenderableTileGroup(Ref<Texture2D> texture, glm::uvec2 size);

        void addCharacter(Ref<RenderableCharacter> renderable);

        bool hasHovered() const;
        size_t getHoveredX() const;
        size_t getHoveredY() const;

        void setHoveredInFocus();
        void clearFocused();

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
    protected:
        uint32_t getTileIndex(uint32_t x, uint32_t y) const;
        void unselectHover();
        void changeHover(uint32_t x, uint32_t y);
    protected:
        static inline Color s_DefaultColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
        static inline Color s_HoveredColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
        static inline Color s_FocusedColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
    protected:
        Ref<Texture2D> m_TextureTile;
        Vector<Ref<RenderableTile>> m_Tiles;
        glm::uvec2 m_Size;

        Vector<Ref<RenderableCharacter>> m_Characters;

        size_t m_HoveredId;
        size_t m_FocusedId;
    };

}    // namespace LM
