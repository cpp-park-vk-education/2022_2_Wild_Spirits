#include "LayerMainMenu.h"

#include <Core/Application.h>
#include <Utils/ConsoleLog.h>
#include <Renderables/Gui/RenderableGuiGroup.h>
#include "LayerLocation.h"

namespace LM {

    LayerMainMenu::LayerMainMenu() {
        LOGI("LayerMainMenu");
        Ref<Texture2D> textureStart = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/Start.png" });
        Ref<Texture2D> textureStartAsDm = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/StartDM.png" });

        m_BtnStart = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ textureStart },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, 100.0f) });
        m_BtnStartDM = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ textureStartAsDm },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, 0.0f) });
        Ref<RenderableGuiGroup> buttonGroup = CreateRef<RenderableGuiGroup>(Vector<Ref<RenderableGui>>({ m_BtnStart, m_BtnStartDM }), 
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter } });
        addToGui(buttonGroup);
    }

    LayerMainMenu::~LayerMainMenu() {

    }

    void LayerMainMenu::onEvent(Ref<Event> event) {
        Layer::onEvent(event);
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>([&](Ref<MouseButtonPressedEvent> e) {
            if (m_BtnStart->isHovered()) {
                handleStart();
                return false;
            }
            if (m_BtnStartDM->isHovered()) {
                handleStartDM();
                return false;
            }
            return false;
        });
    }


    void LayerMainMenu::onUpdate(Tick tick) {
        Layer::onUpdate(tick);
    }
    

    void LayerMainMenu::handleStart() {
        Application::get()->addLayer(CreateRef<LayerLocation>());
        Application::get()->removeLayer(this);
    }

    void LayerMainMenu::handleStartDM() {
        Application::get()->addLayer(CreateRef<LayerLocation>());
        Application::get()->removeLayer(this);
    }

}
