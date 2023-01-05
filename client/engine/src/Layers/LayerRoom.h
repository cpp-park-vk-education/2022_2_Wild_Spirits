#pragma once

#include "Layer.h"

#include "Classes/Room.h"

namespace LM {

    class LayerRoom : public Layer {
    public:
        explicit LayerRoom(Room room, bool isUserCreator = false);

        virtual void onUpdate(Tick tick) override;
        virtual void renderImGui() override;

    protected:
        void goToMainMenu();
        void startGame();

    protected:
        bool m_NeedStart = false;
        Room m_Room;

        bool m_IsUserCreator;
    };

}    // namespace LM
