#include "LayerRegister.h"

#include <ImGui/ImGuiFuncs.h>

#include <misc/cpp/imgui_stdlib.h>

#include <Core/Application.h>
#include "LayerMainMenu.h"

namespace LM {

    void LayerRegister::onUpdate(Tick tick) {
        (void)tick;
        if (m_NeedRemove) {
            Application::get()->addLayer(CreateRef<LayerMainMenu>());
            Application::get()->removeLayer(this);
            return;
        }
    }

    void LayerRegister::renderImGui() {
        if (ImGui::Begin("Register", 0, ImGuiFuncs::SetNextWindowCenterAutoResize())) {
            ImGui::InputText("Login##Field", &m_Login);
            ImGui::InputText("Password##Field", &m_Password, ImGuiInputTextFlags_Password);

            if (ImGui::Button("Register")) {
                handleBtn();
            }
        }
        ImGui::End();
    }

    void LayerRegister::handleBtn() {
        m_NeedRemove = true;
    }

}    // namespace LM
