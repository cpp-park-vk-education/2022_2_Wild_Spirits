#pragma once

#include <string>

#include "Layer.h"

namespace LM {

    class LayerLogin: public Layer {
    public:
        virtual void onUpdate(Tick tick) override;
        virtual void renderImGui() override;
        void handleBtn();
    protected:
        std::string m_Login;
        std::string m_Password;
        bool m_NeedRemove = false;
    };

}
