#include "LayerLocation.h"

#include <Utils/ConsoleLog.h>

namespace LM {
    
    LayerLocation::LayerLocation() {
        
        Vector<Ref<RenderableGui>> bottomItems;
        for (size_t i = 1; i <= 5; ++i) {
            bottomItems.push_back(CreateRef<RenderableGuiTexture>(
                RenderableTextureProps{ CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Skill" + std::to_string(i) + ".png" }), s_BottomActionSize }));
        }
        m_Weapons.push_back(GS::Weapon(0)); m_Weapons.push_back(GS::Weapon(1));
        Ref<Texture2D> textureWeapon = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Skill1.png" });
        
        m_Spells.push_back(GS::Spell(0)); m_Spells.push_back(GS::Spell(1));
        Ref<Texture2D> textureSpell = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Skill2.png" });
        
        m_Skills.push_back(GS::Skill(0)); m_Skills.push_back(GS::Skill(1));
        Ref<Texture2D> textureSkill = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Skill3.png" });

        m_Consumables.push_back(GS::Consumable(0)); m_Consumables.push_back(GS::Consumable(1));
        Ref<Texture2D> textureConsumable = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Skill4.png" });

        Ref<RenderableBottomActionGroup> bottomActions = CreateRef<RenderableBottomActionGroup>(s_BottomActionSpace);
        for (auto& item : m_Weapons) { bottomActions->add(CreateRef<RenderableBottomWeapon>(RenderableTextureProps{ textureWeapon }, item)); }
        for (auto& item : m_Spells) { bottomActions->add(CreateRef<RenderableBottomSpell>(RenderableTextureProps{ textureSpell }, item)); }
        for (auto& item : m_Skills) { bottomActions->add(CreateRef<RenderableBottomSkill>(RenderableTextureProps{ textureSkill }, item)); }
        for (auto& item : m_Consumables) { bottomActions->add(CreateRef<RenderableBottomConsumable>(RenderableTextureProps{ textureConsumable }, item)); }
        addToGui(bottomActions);

        Ref<RenderableTileGroup> tiles = CreateRef<RenderableTileGroup>(
            CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Tile.png" }), glm::uvec2(16, 16));

        addToScene(tiles);
    }

    LayerLocation::~LayerLocation() {

    }

    void LayerLocation::onEvent(Ref<Event> event) {
        Layer::onEvent(event);
    }

    void LayerLocation::onUpdate(Tick tick) {
        Layer::onUpdate(tick);
    }

}
