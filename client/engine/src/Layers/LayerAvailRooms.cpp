#include "LayerAvailRooms.h"

#include "LayerMainMenu.h"
#include "LayerRoom.h"
#include <Core/Application.h>
#include <ImGui/ImGuiFuncs.h>

namespace LM {

    LayerAvailRooms::LayerAvailRooms() { getRooms(); }

    void LayerAvailRooms::goToMainMenu() {
        Application::get()->addLayer(CreateRef<LayerMainMenu>());
        Application::get()->removeLayer(this);
    }

    void LayerAvailRooms::goToRoom(size_t roomId) {
        if (Application::get()->getClientSideProcessor()->ConnectToRoom(m_Rooms[roomId])) {
            Application::get()->addLayer(CreateRef<LayerRoom>(m_Rooms[roomId]));
            Application::get()->removeLayer(this);
            return;
        }
        // TODO set error flag
        getRooms();
    }

    void LayerAvailRooms::onUpdate(Tick tick) { (void)tick; }

    void LayerAvailRooms::renderImGui() {
        if (ImGui::Begin("Rooms", 0, ImGuiFuncs::SetNextWindowCenterAutoResize())) {
            for (size_t i = 0; i < m_Rooms.size(); ++i) {
                ImGui::PushID(static_cast<int>(m_Rooms[i].getId()));
                ImGui::Text("RoomId: %10lu", m_Rooms[i].getId());
                ImGui::SameLine();
                if (ImGui::Button("Connect")) {
                    goToRoom(i);
                }
                ImGui::PopID();
            }
            ImGui::Separator();
            if (ImGui::Button("Go to main menu")) {
                goToMainMenu();
            }
        }
        ImGui::End();
    }

    void LayerAvailRooms::getRooms() {
        m_Rooms.clear();
        m_Rooms = Application::get()->getClientSideProcessor()->GetRooms();
    }

}    // namespace LM
