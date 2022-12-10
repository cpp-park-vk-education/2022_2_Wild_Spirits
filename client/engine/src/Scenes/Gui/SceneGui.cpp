#include "SceneGui.h"

#include <glm/gtx/transform.hpp>

#include <Core/Application.h>
#include <Utils/ConsoleLog.h>
#include <Renderers/Renderer.h>


namespace LM {

    SceneGui::SceneGui() {
        m_Renderer = CreateScope<Renderer>();
        m_Width = Application::get()->getWindow()->getWidth();
        m_Height = Application::get()->getWindow()->getHeight();
    }

    SceneGui::~SceneGui() {

    }

    void SceneGui::rebuild() {
        //m_Transforms.push_back({ glm::mat4(), glm::vec2(0.0f, 0.0f), glm::vec2(m_Width, m_Height) });
        for (auto& renderable : m_Renderables)
        {
            renderable->rebuid(glm::uvec2(m_Width, m_Height));
        }
    }

    void SceneGui::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowResizeEvent>([&](Ref<WindowResizeEvent> event) {
            m_Width = event->getWidth();
            m_Height = event->getHeight();
            return false;
        });

        bool isMouseMovedEvent = false;
        dispatcher.dispatch<MouseMovedEvent>([&](Ref<MouseMovedEvent> e) {
            isMouseMovedEvent = true;
            for (auto& renderable : m_Renderables) {
                Ref<MouseMovedEvent> newEvent = CreateRef<MouseMovedEvent>(e->getX(), m_Height - e->getY());
                renderable->onEvent(newEvent);
            }
            return false;
        });
        if (isMouseMovedEvent) { return; }

        for (auto& renderable : m_Renderables) {
            renderable->onEvent(event);
        }
    }

    void SceneGui::onUpdate(Tick tick) {
        for (auto& renderable : m_Renderables) {
            renderable->onUpdate(tick);
        }
    }

    void SceneGui::render() {
        glm::mat4 viewMatrix = glm::ortho(0.0f, static_cast<float>(m_Width), 0.0f, static_cast<float>(m_Height));
        m_Renderer->start(glm::uvec2(m_Width, m_Height), glm::mat4(1.0f), viewMatrix);
        for (auto& renderable : m_Renderables)
        {
            renderable->drawDecorator(m_Renderer.get());
        }
    }

}
