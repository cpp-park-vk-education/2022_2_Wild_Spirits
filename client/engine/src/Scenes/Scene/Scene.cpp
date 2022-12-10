#include "Scene.h"

#include <Core/Application.h>

namespace LM {

    Scene::Scene() {
        m_Renderer = CreateScope<Renderer>();
    }

    Scene::~Scene() {

    }

    void Scene::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);
        //dispatcher.dispatch<WindowResizeEvent>([&](Ref<WindowResizeEvent> event) {
        //    m_Width = event->getWidth();
        //    m_Height = event->getHeight();
        //    return false;
        //});

        bool isMouseMovedEvent = false;
        dispatcher.dispatch<MouseMovedEvent>([&](Ref<MouseMovedEvent> e) {
            isMouseMovedEvent = true;
            for (auto& renderable : m_Renderables) {
                Ref<MouseMovedEvent> newEvent = CreateRef<MouseMovedEvent>(e->getX(), Application::get()->getWindow()->getHeight() - e->getY());
                renderable->onEvent(newEvent);
            }
            return false;
        });
        if (isMouseMovedEvent) { return; }

        for (auto& renderable : m_Renderables) {
            renderable->onEvent(event);
        }
    }

    void Scene::onUpdate(Tick tick) {
        for (auto& renderable : m_Renderables) {
            renderable->onUpdate(tick);
        }
    }

    void Scene::render() {

        glm::mat4 viewMatrix = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f);
        //m_Renderer->start(glm::uvec2(m_Width, m_Height), glm::mat4(1.0f), viewMatrix);
        m_Renderer->start(glm::uvec2(Application::get()->getWindow()->getWidth(), Application::get()->getWindow()->getHeight()), 
            glm::mat4(1.0f), viewMatrix);
        for (auto& renderable : m_Renderables)
        {
            m_Renderer->pushTransform(renderable->getTransform().getMatrix());
            renderable->draw(m_Renderer.get());
            m_Renderer->popTransform();
        }

    }

}
