#pragma once

#include <Renderables/RenderableGroup.h>
#include "RenderableTile.h"

namespace LM {

    class RenderableTileGroup : public RenderableGroup {
    public:
        RenderableTileGroup(Ref<Texture2D> texture, glm::uvec2 size);
        
        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
    protected:
        uint32_t getTileIndex(uint32_t x, uint32_t y) const;
        void unselectHover();
        void changeHover(uint32_t x, uint32_t y);
    protected:
        Ref<Texture2D> m_TextureTile;
        Vector<Ref<RenderableTile>> m_Tiles;
        glm::uvec2 m_Size;

        size_t m_HoveredId;
    };

}
