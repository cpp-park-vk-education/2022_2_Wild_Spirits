#include "LayerMainMenu.h"

#include "LayerAvailRooms.h"
#include "LayerLogin.h"
#include "LayerRegister.h"
#include "LayerRoom.h"
#include <Core/Application.h>
#include <ImGui/ImGuiFuncs.h>
#include <Renderables/Gui/RenderableGuiGroup.h>
#include <Utils/ConsoleLog.h>

namespace LM {

    LayerMainMenu::LayerMainMenu() {
        LOGI("LayerMainMenu");
        Ref<Texture2D> textureStart =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/MainMenu/Start.png" });
        Ref<Texture2D> textureStartDm =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/MainMenu/StartGM.png" });
        Ref<Texture2D> textureLogin =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/MainMenu/Login.png" });
        Ref<Texture2D> textureReg =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/MainMenu/Register.png" });

        m_BtnStart = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps {
                textureStart
        },
            RenderableGuiProps { { GuiAlign::kCenter, GuiAlign::kCenter }, glm::vec2(0.0f, 120.0f) });
        m_BtnStartDM = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps {
                textureStartDm
        },
            RenderableGuiProps { { GuiAlign::kCenter, GuiAlign::kCenter }, glm::vec2(0.0f, 0.0f) });
        m_BtnLogin = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps {
                textureLogin
        },
            RenderableGuiProps { { GuiAlign::kCenter, GuiAlign::kCenter }, glm::vec2(0.0f, -180.0f) });
        m_BtnRegister = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps {
                textureReg
        },
            RenderableGuiProps { { GuiAlign::kCenter, GuiAlign::kCenter }, glm::vec2(0.0f, -300.0f) });
        Vector<Ref<RenderableGui>> buttons { m_BtnStart, m_BtnStartDM, m_BtnLogin, m_BtnRegister };
        Ref<RenderableGuiGroup> buttonGroup =
            CreateRef<RenderableGuiGroup>(buttons, RenderableGuiProps {
                                                       {GuiAlign::kCenter, GuiAlign::kCenter}
        });
        addToGui(buttonGroup);
    }

    LayerMainMenu::~LayerMainMenu() { }

    void LayerMainMenu::onEvent(Ref<Event> event) {
        Layer::onEvent(event);
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>([&](Ref<MouseButtonPressedEvent> e) {
            const ImGuiIO& io = ImGui::GetIO();
            if (io.WantCaptureMouse) {
                return false;
            }
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

    void LayerMainMenu::onUpdate(Tick tick) { Layer::onUpdate(tick); }

    void LayerMainMenu::renderImGui() {
        if (Application::get()->getClientSideProcessor()->isAuthorized()) {
            if (ImGui::Begin("Auth user info", nullptr, ImGuiFuncs::SetNextWindowOverlayBottomLeft())) {
                ImGui::Text("Username %s", Application::get()->getUserName().c_str());
                if (ImGui::Button("Logout")) {
                }
            }
            ImGui::End();
        }
    }

    void LayerMainMenu::handleLogin() {
        if (Application::get()->getClientSideProcessor()->isAuthorized()) {
            return;
        }
        Application::get()->addLayer(CreateRef<LayerLogin>());
        Application::get()->removeLayer(this);
    }

    void LayerMainMenu::handleRegister() {
        if (Application::get()->getClientSideProcessor()->isAuthorized()) {
            return;
        }
        Application::get()->addLayer(CreateRef<LayerRegister>());
        Application::get()->removeLayer(this);
    }

    void LayerMainMenu::handleStart() {
        if (!Application::get()->getClientSideProcessor()->isAuthorized()) {
            return;
        }
        Application::get()->addLayer(CreateRef<LayerAvailRooms>());
        Application::get()->removeLayer(this);
    }

    void LayerMainMenu::handleStartDM() {
        if (!Application::get()->getClientSideProcessor()->isAuthorized()) {
            return;
        }
        Room room = Application::get()->getClientSideProcessor()->CreateRoom();
        // TODO Check room creation status
        Application::get()->addLayer(CreateRef<LayerRoom>(room, true));
        Application::get()->removeLayer(this);
    }

}    // namespace LM
