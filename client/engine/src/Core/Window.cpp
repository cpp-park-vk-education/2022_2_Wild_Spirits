#include "Window.h"

namespace LM {

    Window::Window(const WindowProps& props)
        : m_Data(props)
    {
        init();
    }

    Window::~Window() {

    }

    void Window::onUpdate() {

    }

    bool Window::init() {
        return true;
    }

    void Window::setCallbacks() {

    }

}
