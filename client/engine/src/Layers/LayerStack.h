#pragma once

#include <Core/Base.h>
#include "Layer.h"

namespace LM {

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void pushLayer(Ref<Layer> layer);
        void popLayer(Ref<Layer> layer);

        void render();
        void onUpdate(Tick tick);
        void onEvent(Ref<Event> event);
    protected:
        std::vector<Ref<Layer>> m_Layers;
    };

}
