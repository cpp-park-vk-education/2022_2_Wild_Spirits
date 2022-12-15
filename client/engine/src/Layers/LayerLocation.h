#pragma once

#include "Layer.h"
#include <Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.h>
#include <Renderables/Scene/RenderableTileGroup.h>
#include <Actions/MoveAction.h>
#include <Actions/UseActions.h>
#include <Textures/TextureManager.h>

namespace LM {

    class LayerLocation: public Layer {
    public:
        LayerLocation(bool isUserCreator = false);
        ~LayerLocation();

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
        virtual void renderImGui() override;
    protected:
        bool hasActions() const;
        void clearActions();
        void load();

#ifdef BUILD_LOGIC
        void tryLoadImage(size_t id);

        template<typename T>
        void loadActivatable(T storage);
#endif
    protected:
        static inline const glm::vec2 s_BottomActionSize = glm::vec2(48.0f, 48.0f);
        static inline const float s_BottomActionSpace = 5.0f;
    protected:
#ifndef BUILD_LOGIC
        Vector<DnD::Weapon> m_Weapons;
        Vector<DnD::Spell> m_Spells;
        Vector<DnD::Skill> m_Skills;
        Vector<DnD::Consumable> m_Consumables;
#endif
        bool m_IsUserCreator;
        Ref<TextureManager> m_TextureManager;

        Ref<RenderableBottomActionGroup> m_BottomActions;
        Ref<RenderableTileGroup> m_Field;

        Ref<Texture2D> m_TileTexture;

        Ref<RenderableGuiTexture> m_BtnCancel;
        Ref<RenderableGuiTexture> m_BtnTurn;

        Ref<MoveAction> m_ActionMove;
        Ref<UseAction> m_ActionUse;
    };

}    // namespace LM
