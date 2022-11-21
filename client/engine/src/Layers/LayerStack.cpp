#include "LayerStack.h"

namespace LM {

    void LayerStack::pushLayer(Ref<Layer> layer) {
        m_Layers.emplace_back(layer);
    }

    void LayerStack::popLayer(Ref<Layer> layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end()) {
            m_Layers.erase(it);
        }
    }

    void LayerStack::onUpdate(Tick tick) {
        for (auto& layer : m_Layers) {
            layer->onUpdate(tick);
        }
    }

    void LayerStack::onEvent(Ref<Event> event) {
        for (auto& layer : m_Layers) {
            layer->onEvent(event);
        }
    }

}
