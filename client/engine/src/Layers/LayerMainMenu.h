#pragma once

#include "Layer.h"

namespace LM {

    class LayerMainMenu : public Layer {
    public:
        LayerMainMenu();
        ~LayerMainMenu();

        virtual void onEvent(Ref<Event> _Event);
        virtual void onUpdate(Tick tick);
    protected:
    };

}
