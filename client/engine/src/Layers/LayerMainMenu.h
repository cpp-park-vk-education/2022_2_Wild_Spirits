#pragma once

#include "Layer.h"
#include <Renderables/Gui/RenderableGuiTexture.h>

namespace LM {

    class LayerMainMenu: public Layer {
    public:
        LayerMainMenu();
        ~LayerMainMenu();

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;
    protected:
        void handleStart();
        void handleStartDM();
        void handleLogin();
        void handleRegister();
    protected:
        Ref<RenderableGuiTexture> m_BtnStart;
        Ref<RenderableGuiTexture> m_BtnStartDM;
        Ref<RenderableGuiTexture> m_BtnLogin;
        Ref<RenderableGuiTexture> m_BtnRegister;
    };

}    // namespace LM
