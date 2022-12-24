#include "LayerStack.h"

#include <algorithm>

namespace LM {

    void LayerStack::pushLayer(Ref<Layer> layer) { m_LayersToAdd.emplace_back(layer); }

    void LayerStack::popLayer(Ref<Layer> layer) { m_LayersToRemove.emplace_back(layer.get()); }

    void LayerStack::popLayer(Layer* layer) { m_LayersToRemove.emplace_back(layer); }

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

    void LayerStack::updateLayersState() {
        for (const auto& layer : m_LayersToAdd) {
            m_Layers.emplace_back(layer);
        }
        m_LayersToAdd.clear();

        for (auto layer : m_LayersToRemove) {
            if (auto it = std::find_if(m_Layers.begin(), m_Layers.end(),
                                       [&](Ref<Layer> stackLayer) { return stackLayer.get() == layer; });
                it != m_Layers.end()) {
                m_Layers.erase(it);
            }
        }
        m_LayersToRemove.clear();
    }

}    // namespace LM
