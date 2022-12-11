#pragma once

#include "Layer.h"

#include "Classes/Room.h"

namespace LM {

    class LayerRoom : public Layer {
    public:
        LayerRoom(Room room, bool isUserCreator = false);

        virtual void onUpdate(Tick tick) override;
        virtual void renderImGui();
    protected:
        void goToMainMenu();
        void startGame();
    protected:
        bool m_NeedGoBack = false;
        bool m_NeedStart = false;
        bool m_IsUserCreator;

        Room m_Room;
    };

}
