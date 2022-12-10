#pragma once

#include "Layer.h"
#include <Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.h>
#include <Renderables/Scene/RenderableTileGroup.h>

namespace LM {

    class LayerLocation : public Layer {
    public:
        LayerLocation();
        ~LayerLocation();

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
    protected:
        static inline const glm::vec2 s_BottomActionSize = glm::vec2(48.0f, 48.0f);
        static inline const float s_BottomActionSpace = 5.0f;
    protected:
        Vector<GS::Weapon> m_Weapons;
        Vector<GS::Spell> m_Spells;
        Vector<GS::Skill> m_Skills;
        Vector<GS::Consumable> m_Consumables;
    };

}
