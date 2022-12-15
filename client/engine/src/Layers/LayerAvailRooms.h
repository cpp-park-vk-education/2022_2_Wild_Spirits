#pragma once

#include "Layer.h"

#include "Classes/Room.h"

namespace LM {

    class LayerAvailRooms: public Layer {
    public:
        LayerAvailRooms();
        virtual void onUpdate(Tick tick) override;
        virtual void renderImGui();
    protected:
        void goToMainMenu();
        void goToRoom();

        void getRooms();
    protected:
        std::vector<Room> m_Rooms;

        bool m_NeedGoBack = false;
        bool m_NeedGoToRoom = false;
        size_t m_RoomId = 0;
    };

}    // namespace LM
