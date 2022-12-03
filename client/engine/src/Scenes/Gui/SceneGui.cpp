#include "SceneGui.h"

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

    }

    void SceneGui::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowResizeEvent>([&](Ref<WindowResizeEvent> event) {
            LOGI("WindowResizeEvent");
            m_Width = event->getWidth();
            m_Height = event->getHeight();
            return false;
        });
    }

    void SceneGui::render() {
        m_Renderer->start();
        for (auto& el : m_Renderables)
        {
            el->draw(m_Renderer.get());
        }
    }

}
