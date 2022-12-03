#include "Scene.h"

namespace LM {

    Scene::Scene() {
        m_Renderer = CreateScope<Renderer>();
    }

    Scene::~Scene() {

    }

    void Scene::onEvent(Ref<Event> event) {

    }

    void Scene::render() {
        m_Renderer->start();

    }

}
