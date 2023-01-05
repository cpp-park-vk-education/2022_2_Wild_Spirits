#include "Layer.h"

namespace LM {

    Layer::Layer() : m_SceneScene(CreateRef<Scene>()), m_SceneGui(CreateRef<SceneGui>()) { }

    void Layer::render() {
        m_SceneScene->render();
        m_SceneGui->render();
    }

    void Layer::clearScenes() {
        m_SceneGui->clear();
        m_SceneScene->clear();
    }

    void Layer::onEvent(Ref<Event> _Event) {
        m_SceneGui->onEvent(_Event);
        m_SceneScene->onEvent(_Event);
    }

    void Layer::onUpdate(Tick tick) {
        m_SceneGui->rebuild();
        m_SceneGui->onUpdate(tick);
        m_SceneScene->onUpdate(tick);
    }

}    // namespace LM
