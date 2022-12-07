#include "LayerMainMenu.h"

#include <Utils/ConsoleLog.h>
#include <Renderables/Gui/RenderableGuiTexture.h>
#include <Renderables/Gui/RenderableGuiGroup.h>
#include <Renderables/Gui/RenderableBottomAction/RenderableBottomActionGroup.h>

namespace LM {

    LayerMainMenu::LayerMainMenu() {
        LOGI("LayerMainMenu");
        uint8_t testData[] = { 0x00, 0xff, 0x00, 0xff };
        Ref<RenderableGuiTexture> startBtn = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Start.png" }) },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, 100.0f) });
        Ref<RenderableGuiTexture> startDmBtn = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/StartDM.png" }) },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, 0.0f) });
        Ref<RenderableGuiGroup> buttonGroup = CreateRef<RenderableGuiGroup>(Vector<Ref<RenderableGui>>({ startBtn, startDmBtn }), 
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter } });
        addToGui(buttonGroup);
        

        Vector<Ref<RenderableGui>> bottomItems;
        for (size_t i = 1; i <= 5; ++i) {
            bottomItems.push_back(CreateRef<RenderableGuiTexture>( 
                RenderableTextureProps{ CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Skill" + std::to_string(i) + ".png" }) }));
        }

        Ref<RenderableBottomActionGroup> bottomActions = CreateRef<RenderableBottomActionGroup>(5.0f, bottomItems);
        addToGui(bottomActions);
    }

    LayerMainMenu::~LayerMainMenu() {

    }

    void LayerMainMenu::onUpdate(Tick tick) {
        Layer::onUpdate(tick);
    }

}
