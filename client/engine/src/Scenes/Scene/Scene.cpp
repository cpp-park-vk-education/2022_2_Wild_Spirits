#include "Scene.h"

#include <algorithm>

#include <Core/Application.h>

namespace LM {

    Scene::Scene() {
        m_Renderer = CreateScope<Renderer>();
    }

    Scene::~Scene() {
    }

    void Scene::add(Ref<RenderableInterface> renderable) {
        m_Renderables.emplace_back(renderable);
    }

    void Scene::remove(Ref<RenderableInterface> renderable) {
        if (auto it = std::find(m_Renderables.begin(), m_Renderables.end(), renderable); it != m_Renderables.end()) {
            m_Renderables.erase(it);
        }
    }

    void Scene::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);

        bool isMouseMovedEvent = false;
        dispatcher.dispatch<MouseMovedEvent>([&](Ref<MouseMovedEvent> e) {
            isMouseMovedEvent = true;
        for (auto& renderable : m_Renderables) {
            Ref<MouseMovedEvent> newEvent = CreateRef<MouseMovedEvent>(
                e->getX(),
                Application::get()->getWindow()->getHeight() - e->getY());
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
        m_Renderer->start(
            glm::uvec2(Application::get()->getWindow()->getWidth(), Application::get()->getWindow()->getHeight()),
            glm::mat4(1.0f),
            viewMatrix);
        for (auto& renderable : m_Renderables) {
            m_Renderer->pushTransform(renderable->getTransform().getMatrix());
            renderable->draw(m_Renderer.get());
            m_Renderer->popTransform();
        }
    }

}    // namespace LM
