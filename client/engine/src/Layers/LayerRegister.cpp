#include "LayerRegister.h"

#include <ImGui/ImGuiFuncs.h>

#include <misc/cpp/imgui_stdlib.h>

#include "LayerMainMenu.h"
#include <Core/Application.h>

namespace LM {

    void LayerRegister::onUpdate(Tick tick) { (void)tick; }

    void LayerRegister::renderImGui() {
        if (ImGui::Begin("Register", 0, ImGuiFuncs::SetNextWindowCenterAutoResize())) {
            if (ImGui::Button("Back")) {
                Application::get()->addLayer(CreateRef<LayerMainMenu>());
                Application::get()->removeLayer(this);
            }
            ImGui::Separator();
            ImGui::InputText("Login##Field", &m_Login);
            ImGui::InputText("Password##Field", &m_Password, ImGuiInputTextFlags_Password);

            if (ImGui::Button("Register")) {
                handleBtn();
            }
            if (m_ShowWrongData) {
                ImGui::TextUnformatted("Username exists!");
            }
        }
        ImGui::End();
    }

    void LayerRegister::handleBtn() {
        if (Application::get()->getClientSideProcessor()->Register(m_Login, m_Password)) {
            Application::get()->setUserName(m_Login);
            Application::get()->addLayer(CreateRef<LayerMainMenu>());
            Application::get()->removeLayer(this);
            return;
        }
        m_ShowWrongData = true;
    }

}    // namespace LM
