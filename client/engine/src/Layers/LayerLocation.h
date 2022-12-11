#pragma once

#include "Layer.h"
#include <Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.h>
#include <Renderables/Scene/RenderableTileGroup.h>
#include <Actions/MoveAction.h>
#include <Actions/UseActions.h>

namespace LM {

    class LayerLocation : public Layer {
    public:
        LayerLocation();
        ~LayerLocation();

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
        virtual void renderImGui() override;
    protected:
        bool hasActions() const;
        void clearActions();
    protected:
        static inline const glm::vec2 s_BottomActionSize = glm::vec2(48.0f, 48.0f);
        static inline const float s_BottomActionSpace = 5.0f;
    protected:
        Vector<DnD::Weapon> m_Weapons;
        Vector<DnD::Spell> m_Spells;
        Vector<DnD::Skill> m_Skills;
        Vector<DnD::Consumable> m_Consumables;

        Ref<RenderableBottomActionGroup> m_BottomActions;
        Ref<RenderableTileGroup> m_Field;

        Ref<RenderableGuiTexture> m_BtnCancel;
        Ref<RenderableGuiTexture> m_BtnTurn;

        Ref<MoveAction> m_ActionMove;
        Ref<UseAction> m_ActionUse;
    };

}
