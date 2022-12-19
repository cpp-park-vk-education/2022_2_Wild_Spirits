#pragma once

#include "Layer.h"
#include <Core/Base.h>

namespace LM {

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void pushLayer(Ref<Layer> layer);
        void popLayer(Ref<Layer> layer);
        void popLayer(Layer* layer);

        void render();
        void renderImGui();
        void onUpdate(Tick tick);
        void onEvent(Ref<Event> event);
        void updateLayersState();

    protected:
        std::vector<Ref<Layer>> m_Layers;
        std::vector<Ref<Layer>> m_LayersToAdd;
        std::vector<Layer*> m_LayersToRemove;
    };

}    // namespace LM
