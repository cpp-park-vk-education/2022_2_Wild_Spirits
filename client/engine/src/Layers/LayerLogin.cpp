#include "LayerLogin.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <Core/Application.h>
#include "LayerMainMenu.h"

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
        ImGuiIO& io = ImGui::GetIO(); //(void)io;
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        if (ImGui::Begin("Login", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::InputText("Login##Field", &m_Login);
            ImGui::InputText("Password##Field", &m_Password, ImGuiInputTextFlags_Password);

            if (ImGui::Button("Login")) {
                handleBtn();
            }
        }
        ImGui::End();
    }

    void LayerLogin::handleBtn() {
        // Send to server, if res ok go to main menu
        m_NeedRemove = true;
    }

}
