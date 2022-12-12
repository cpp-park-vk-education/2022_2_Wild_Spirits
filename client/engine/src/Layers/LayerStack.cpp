#include "LayerStack.h"

#include <algorithm>

namespace LM {

    void LayerStack::pushLayer(Ref<Layer> layer) {
        m_Layers.emplace_back(layer);
    }

    void LayerStack::popLayer(Ref<Layer> layer) {
        if (auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); it != m_Layers.end()) {
            m_Layers.erase(it);
        }
    }

    void LayerStack::popLayer(Layer* layer) {
        if (auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&](Ref<Layer> stackLayer) { return stackLayer.get() == layer; }); it != m_Layers.end()) {
            m_Layers.erase(it);
        }
    }


    void LayerStack::render() {
        for (auto& layer : m_Layers) {
            layer->render();
        }
    }

    void LayerStack::renderImGui() {
        for (auto& layer : m_Layers) {
            layer->renderImGui();
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
