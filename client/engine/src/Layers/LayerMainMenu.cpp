#include "LayerMainMenu.h"

#include <Utils/ConsoleLog.h>
#include <Renderables/Gui/RenderableGuiTexture.h>

namespace LM {

    LayerMainMenu::LayerMainMenu() {
        LOGI("LayerMainMenu");
        addToGui(CreateRef<RenderableGuiTexture>(CreateRef<Texture2D>(Texture2D::FromSource{"none"})));
    }

    LayerMainMenu::~LayerMainMenu() {

    }

    void LayerMainMenu::onUpdate(Tick tick) {
        Layer::onUpdate(tick);
    }

}
