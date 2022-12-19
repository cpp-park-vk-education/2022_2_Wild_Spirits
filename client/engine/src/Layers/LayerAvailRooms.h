#pragma once

#include "Layer.h"

#include "Classes/Room.h"

namespace LM {

    class LayerAvailRooms: public Layer {
    public:
        LayerAvailRooms();
        virtual void onUpdate(Tick tick) override;
        virtual void renderImGui() override;
    protected:
        void goToMainMenu();
        void goToRoom(size_t roomId);

        void getRooms();
    protected:
        std::vector<Room> m_Rooms;
    };

}    // namespace LM
