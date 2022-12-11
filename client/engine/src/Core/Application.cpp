#include "Application.h"

#include "Utils/ConsoleLog.h"
#include "Layers/LayerMainMenu.h"

namespace LM {

    Application::Application() {
        LOG_INIT();
        init();
    }

    void Application::init() {
        m_EventQueue = CreateRef<EventQueue>();
        m_Window = CreateRef<Window>();
        m_Window->setEventCallback(m_EventQueue);
        s_Instance = this;
    }

    void Application::run() {
        m_LayerStack = CreateRef<LayerStack>();
        m_LayerStack->pushLayer(CreateRef<LayerMainMenu>());
        m_ImGuiController = CreateRef<ImGuiController>();

        while (m_IsRun) {
            while (!m_EventQueue->empty()) {
                Ref<Event> event = m_EventQueue->pop();
                onEvent(event);
                m_LayerStack->onEvent(event);
            }

            m_LayerStack->onUpdate(0.0f);
            m_LayerStack->render();
        
            m_ImGuiController->begin();
            m_LayerStack->renderImGui();
            m_ImGuiController->end();

            m_Window->onUpdate();
        }
    }

    void Application::onEvent(Ref<Event> event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>([&](Ref<WindowCloseEvent> event) {
            m_IsRun = false;
            return false;
        });
    }


}
