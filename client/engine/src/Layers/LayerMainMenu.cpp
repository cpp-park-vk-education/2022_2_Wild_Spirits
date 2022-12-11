#include "LayerMainMenu.h"

#ifdef BUILD_LOGIC
#include <ClientRequestor.h>
#endif

#include <Core/Application.h>
#include <Utils/ConsoleLog.h>
#include <Renderables/Gui/RenderableGuiGroup.h>
#include "LayerAvailRooms.h"
#include "LayerRoom.h"
#include "LayerLogin.h"
#include "LayerRegister.h"

namespace LM {

    LayerMainMenu::LayerMainMenu() {
        LOGI("LayerMainMenu");
        Ref<Texture2D> textureStart = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/MainMenu/Start.png" });
        Ref<Texture2D> textureStartAsDm = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/MainMenu/StartGM.png" });
        Ref<Texture2D> textureLogin = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/MainMenu/Login.png" });
        Ref<Texture2D> textureRegister = CreateRef<Texture2D>(Texture2D::FromFile{ "./ClientRes/Textures/MainMenu/Register.png" });

        m_BtnStart = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ textureStart },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, 120.0f) });
        m_BtnStartDM = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ textureStartAsDm },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, 0.0f) });
        m_BtnLogin = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ textureLogin },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, -180.0f) });
        m_BtnRegister = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps{ textureRegister },
            RenderableGuiProps{ { RenderableGuiAlign::Align::kCenter, RenderableGuiAlign::Align::kCenter }, glm::vec2(0.0f, -300.0f) });
        Ref<RenderableGuiGroup> buttonGroup = CreateRef<RenderableGuiGroup>(Vector<Ref<RenderableGui>>({ m_BtnStart, m_BtnStartDM, m_BtnLogin, m_BtnRegister }), 
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
            if (m_BtnLogin->isHovered()) {
                handleLogin();
                return false;
            }
            if (m_BtnRegister->isHovered()) {
                handleRegister();
                return false;
            }
            return false;
        });
    }

    void LayerMainMenu::onUpdate(Tick tick) {
        Layer::onUpdate(tick);
    }
    

    void LayerMainMenu::handleStart() {
        Application::get()->addLayer(CreateRef<LayerAvailRooms>());
        Application::get()->removeLayer(this);
    }

    void LayerMainMenu::handleLogin() {
        Application::get()->addLayer(CreateRef<LayerLogin>());
        Application::get()->removeLayer(this);
    }

    void LayerMainMenu::handleRegister() {
        Application::get()->addLayer(CreateRef<LayerRegister>());
        Application::get()->removeLayer(this);
    }

#ifdef BUILD_LOGIC
    void LayerMainMenu::handleStartDM() {
        Application::get()->addLayer(CreateRef<LayerRoom>(Room({ 0 }), true));
        Application::get()->removeLayer(this);
    }
#else
    void LayerMainMenu::handleStartDM() {
        Application::get()->addLayer(CreateRef<LayerRoom>(Room({ 0 }), true));
        Application::get()->removeLayer(this);
    }
#endif

}
