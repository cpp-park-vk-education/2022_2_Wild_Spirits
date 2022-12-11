#include "LayerRoom.h"

#include <imgui.h>

#include <Core/Application.h>
#include "LayerMainMenu.h"
#include "LayerLocation.h"

namespace LM {

    LayerRoom::LayerRoom(Room room, bool isUserCreator) 
        : m_Room(room), m_IsUserCreator(isUserCreator)
    {

    }

    void LayerRoom::goToMainMenu() {
        Application::get()->addLayer(CreateRef<LayerMainMenu>());
        Application::get()->removeLayer(this);
    }

    void LayerRoom::startGame() {
        Application::get()->addLayer(CreateRef<LayerLocation>());
        Application::get()->removeLayer(this);
    }

    void LayerRoom::onUpdate(Tick tick) {
        if (m_NeedGoBack) {
            goToMainMenu();
            return;
        }
        if (m_NeedStart) {
            startGame();
            return;
        }
    }

    void LayerRoom::renderImGui() {
        ImGuiIO& io = ImGui::GetIO(); //(void)io;
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        if (ImGui::Begin("Room", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
            for (auto& userName : std::vector<std::string>{ "LENIA", "MIHAIL", "MAKS", "NIKITA" }) {
                ImGui::Text(userName.data());
            }
            ImGui::Separator();
            if (m_IsUserCreator && ImGui::Button("Start Game")) {
                m_NeedStart = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Go to main menu")) {
                m_NeedGoBack = true;
            }
        }
        ImGui::End();
    }

}
