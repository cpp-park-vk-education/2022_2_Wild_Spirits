#include "Scene.h"

#include <Core/Application.h>

namespace LM {

    Scene::Scene() {
        m_Renderer = CreateScope<Renderer>();
    }

    Scene::~Scene() {

    }

    void Scene::onEvent(Ref<Event> event) {

    }

    void Scene::onUpdate(Tick tick) {
        for (auto& el : m_Renderables) {
            el->onUpdate(tick);
        }
    }

    void Scene::render() {
        m_Renderer->start(glm::uvec2(Application::get()->getWindow()->getWidth(), Application::get()->getWindow()->getHeight()), 
            glm::mat4(1.0f), glm::mat4(1.0f));

    }

}
