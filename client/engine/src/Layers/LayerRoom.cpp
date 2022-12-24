#include "LayerRoom.h"

#include <ImGui/ImGuiFuncs.h>

#include <imgui.h>

#include "LayerLocation.h"
#include "LayerMainMenu.h"
#include <Core/Application.h>

namespace LM {

    LayerRoom::LayerRoom(Room room, bool isUserCreator) : m_Room(room), m_IsUserCreator(isUserCreator) { }

    void LayerRoom::goToMainMenu() {
        Application::get()->addLayer(CreateRef<LayerMainMenu>());
        Application::get()->removeLayer(this);
    }

    void LayerRoom::startGame() {
        if (m_IsUserCreator) {
            if (Application::get()->getClientSideProcessor()->StartGame()) {
                Application::get()->addLayer(CreateRef<LayerLocation>(m_IsUserCreator));
                Application::get()->removeLayer(this);
            }
            return;
        }
    }

    void LayerRoom::onUpdate(Tick tick) {
        (void)tick;

        // TOOD Some Check for users(not GM) that GM start the game
    }

    void LayerRoom::renderImGui() {
        if (ImGui::Begin("Room", 0, ImGuiFuncs::SetNextWindowCenterAutoResize())) {
            if (!m_IsUserCreator) {
                ImGui::Text("Wait for GM to start the game");
                ImGui::Separator();
            }
            for (auto& userName : std::vector<std::string> { "LENIA", "MIHAIL", "MAKS", "NIKITA" }) {
                ImGui::Text("%s", userName.data());
            }
            ImGui::Separator();
            if (m_IsUserCreator && ImGui::Button("Start Game")) {
                startGame();
            }
            ImGui::SameLine();
            if (ImGui::Button("Go to main menu")) {
                goToMainMenu();
            }
        }
        ImGui::End();
    }

}    // namespace LM
