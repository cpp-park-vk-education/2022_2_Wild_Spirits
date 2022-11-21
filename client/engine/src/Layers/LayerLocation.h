#pragma once

#include "Layer.h"

namespace LM {

    class LayerLocation : public Layer {
    public:
        LayerLocation();
        ~LayerLocation();

        virtual void onEvent(Ref<Event> _Event);
        virtual void onUpdate(Tick tick);
    protected:
    };

}