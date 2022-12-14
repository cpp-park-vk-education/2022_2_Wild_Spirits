#pragma once

#include <string>

#include <Core/Base.h>
#include <Events/EventQueue.h>

struct GLFWwindow;

namespace LM {

    struct WindowProps {
        std::string title = "DND";
        uint32_t width = 1280u;
        uint32_t height = 720u;
    };

    class Window {
    public:
        explicit Window(const WindowProps& props = WindowProps());
        ~Window();

        uint32_t getWidth() const { return m_Data.width; }
        uint32_t getHeight() const { return m_Data.height; }

        void onUpdate();

        void setEventCallback(const Ref<EventQueue> eventQueue) { m_Data.eventQueue = eventQueue; }
        GLFWwindow* getNativeWindow() const { return m_Window; }

    private:
        bool init();
        void setCallbacks();

    private:
        struct WindowData : WindowProps {
            explicit WindowData(const WindowProps& props) : WindowProps(props) { }
            Ref<EventQueue> eventQueue;
        };

    private:
        GLFWwindow* m_Window;
        WindowData m_Data;
    };

}    // namespace LM
