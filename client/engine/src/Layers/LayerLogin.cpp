#include "LayerLogin.h"

#include <ImGui/ImGuiFuncs.h>

#include <misc/cpp/imgui_stdlib.h>

#include "LayerMainMenu.h"
#include <Core/Application.h>

namespace LM {

    void LayerLogin::onUpdate(Tick tick) { (void)tick; }

    void LayerLogin::renderImGui() {
        if (ImGui::Begin("Login", 0, ImGuiFuncs::SetNextWindowCenterAutoResize())) {
            ImGui::InputText("Login##Field", &m_Login);
            ImGui::InputText("Password##Field", &m_Password, ImGuiInputTextFlags_Password);

            if (ImGui::Button("Login")) {
                handleBtn();
            }
            if (m_ShowWrongData) {
                ImGui::TextUnformatted("Wrong username or password!");
            }
        }
        ImGui::End();
    }

    void LayerLogin::handleBtn() {
        if (Application::get()->getClientSideProcessor()->Login(m_Login, m_Password)) {
            Application::get()->addLayer(CreateRef<LayerMainMenu>());
            Application::get()->removeLayer(this);
            return;
        }
        m_ShowWrongData = true;
    }

}    // namespace LM
