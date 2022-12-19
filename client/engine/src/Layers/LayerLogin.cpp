#include "LayerLogin.h"

#include <ImGui/ImGuiFuncs.h>

#include <misc/cpp/imgui_stdlib.h>

#include "LayerMainMenu.h"
#include <Core/Application.h>

namespace LM {

    void LayerLogin::onUpdate(Tick tick) {
        (void)tick;
        if (m_NeedRemove) {
            Application::get()->addLayer(CreateRef<LayerMainMenu>());
            Application::get()->removeLayer(this);
            return;
        }
    }

    void LayerLogin::renderImGui() {
        if (ImGui::Begin("Login", 0, ImGuiFuncs::SetNextWindowCenterAutoResize())) {
            ImGui::InputText("Login##Field", &m_Login);
            ImGui::InputText("Password##Field", &m_Password, ImGuiInputTextFlags_Password);

            if (ImGui::Button("Login")) {
                handleBtn();
            }
        }
        ImGui::End();
    }

    void LayerLogin::handleBtn() { m_NeedRemove = true; }

}    // namespace LM
