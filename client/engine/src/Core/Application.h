#pragma once

#include "Base.h"
#include <Core/Window.h>
#include <Layers/LayerStack.h>
#include <Events/EventQueue.h>

namespace LM {

    class Application {
    public:
        Application();

        void run();

        static Application* get() { return s_Instance; }

        Ref<const Window> getWindow() const { return m_Window; }
    private:
        void init();
        void onEvent(Ref<Event> event);
    private:
        Ref<Window> m_Window;
        Ref<LayerStack> m_LayerStack;
        Ref<EventQueue> m_EventQueue;

        bool m_IsRun = true;

        static inline Application* s_Instance;
    };

}
