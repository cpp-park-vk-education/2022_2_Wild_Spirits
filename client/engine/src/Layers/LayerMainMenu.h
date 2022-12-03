#pragma once

#include "Layer.h"

namespace LM {

    class LayerMainMenu : public Layer {
    public:
        LayerMainMenu();
        ~LayerMainMenu();

        virtual void onUpdate(Tick tick) override;
    protected:
    };

}
