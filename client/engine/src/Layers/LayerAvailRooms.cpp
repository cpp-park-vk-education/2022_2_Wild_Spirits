#include "LayerAvailRooms.h"

#include "imgui.h"

#include <Core/Application.h>
#include "LayerMainMenu.h"
#include "LayerRoom.h"

namespace LM {

    LayerAvailRooms::LayerAvailRooms() {
        getRooms();
    }

    void LayerAvailRooms::goToMainMenu() {
        Application::get()->addLayer(CreateRef<LayerMainMenu>());
        Application::get()->removeLayer(this);
    }

    void LayerAvailRooms::goToRoom() {
#ifdef BUILD_LOGIC
        if (Application::get()->getClientSideProcessor()->ConnectToRoom(m_Rooms[m_RoomId].getId())) {
            Application::get()->addLayer(CreateRef<LayerRoom>(m_Rooms[m_RoomId]));
            Application::get()->removeLayer(this);
            return;
        }
        m_NeedGoToRoom = false;
        getRooms();
#else
        Application::get()->addLayer(CreateRef<LayerRoom>(m_Rooms[m_RoomId]));
        Application::get()->removeLayer(this);
#endif
    }

    void LayerAvailRooms::onUpdate(Tick tick) {
        (void)tick;
        if (m_NeedGoBack) {
            goToMainMenu();
            return;
        }
        if (m_NeedGoToRoom) {
            goToRoom();
            return;
        }
    }

    void LayerAvailRooms::renderImGui() {
        ImGuiIO& io = ImGui::GetIO(); //(void)io;
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        if (ImGui::Begin("Rooms", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
            for (size_t i = 0; i < m_Rooms.size(); ++i) {
                ImGui::PushID(static_cast<int>(m_Rooms[i].getId()));
                ImGui::Text("RoomId: %10lu", m_Rooms[i].getId());
                ImGui::SameLine();
                if (ImGui::Button("Connect")) {
                    m_RoomId = i;
                    m_NeedGoToRoom = true;
                }
                ImGui::PopID();
            }
            ImGui::Separator();
            if (ImGui::Button("Go to main menu")) {
                m_NeedGoBack = true;
            }
        }
        ImGui::End();
    }

#ifdef BUILD_LOGIC
    void LayerAvailRooms::getRooms() {
        m_Rooms.clear();
        m_Rooms = Application::get()->getClientSideProcessor()->GetRooms();
    }
#else
    void LayerAvailRooms::getRooms() {
        m_Rooms.clear();
        m_Rooms.emplace_back(RoomProps{ 0 });
        m_Rooms.emplace_back(RoomProps{ 1 });
        m_Rooms.emplace_back(RoomProps{ 2 });
        m_Rooms.emplace_back(RoomProps{ 3 });
    }
#endif


}
