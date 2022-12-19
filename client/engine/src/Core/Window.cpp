#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Events/Events.h>
#include <Utils/ConsoleLog.h>

namespace LM {

#ifdef _DEBUG
    static void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                 const GLchar* message, const void* user_param) {
        (void)length;
        (void)user_param;

        const auto src_str = [source]() {
            switch (source) {
                case GL_DEBUG_SOURCE_API: return "API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
                case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
                case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
                case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
                case GL_DEBUG_SOURCE_OTHER: return "OTHER";
            }
            return "OTHER";
        }();

        const auto type_str = [type]() {
            switch (type) {
                case GL_DEBUG_TYPE_ERROR: return "ERROR";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
                case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
                case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
                case GL_DEBUG_TYPE_MARKER: return "MARKER";
                case GL_DEBUG_TYPE_OTHER: return "OTHER";
            }
            return "OTHER";
        }();

        const auto severity_str = [severity]() {
            switch (severity) {
                case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
                case GL_DEBUG_SEVERITY_LOW: return "LOW";
                case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
                case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
            }
            return "OTHER";
        }();
        LOGE(src_str, ":", type_str, ":", severity_str, ":", id, ":", message);
        if (severity == GL_DEBUG_SEVERITY_HIGH) {
            DEBUGBREAK();
        }
    }
#endif

    Window::Window(const WindowProps& props) : m_Data(props) {
        init();
#ifdef _DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(message_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr,
                              GL_FALSE);
#endif
    }

    Window::~Window() { glfwDestroyWindow(m_Window); }

    void Window::onUpdate() {
        glfwMakeContextCurrent(m_Window);
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    bool Window::init() {
        if (!glfwInit()) {
            LOGE("Failed to initialize GLFW!");
            return false;
        }

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

        m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), NULL, NULL);

        if (!m_Window) {
            LOGE("Failed to create window!");
            return false;
        }

        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);

        setCallbacks();

        glfwSwapInterval(0);

        if (glewInit() != GLEW_OK) {
            LOGE("Could not initialise GLEW!");
            return false;
        }

        glEnable(GL_BLEND);
        // glEnable(GL_ALPHA_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        LOGI("OpenGL version: ", glGetString(GL_VERSION));
        LOGI("OpenGL vendor: ", glGetString(GL_VENDOR));
        LOGI("OpenGL renderer: ", glGetString(GL_RENDERER));
        // LOGI("OpenGL extensions: ", glGetString(GL_EXTENSIONS));
        LOGI("OpenGL shading language version: ", glGetString(GL_SHADING_LANGUAGE_VERSION));

        GLint texture_units;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
        LOGI("Number of textures can be acessed by fragment shader: ", texture_units);
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texture_units);
        LOGI("Max texture units: ", texture_units);

        return true;
    }

    void Window::setCallbacks() {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* _Window, int _Width, int _Height) {
            WindowData* Data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(_Window));
            Data->width = _Width;
            Data->height = _Height;
            Data->eventQueue->add(CreateRef<WindowResizeEvent>(_Width, _Height));
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* _Window) {
            WindowData* Data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(_Window));
            Data->eventQueue->add(CreateRef<WindowCloseEvent>());
        });

        glfwSetKeyCallback(
            m_Window, [](GLFWwindow* _Window, int _Key, int _ScanCode, int _Action, int _Mods) {
                (void)_ScanCode;
                (void)_Mods;
                WindowData* Data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(_Window));
                switch (_Action) {
                    case GLFW_PRESS: Data->eventQueue->add(CreateRef<KeyPressedEvent>(_Key, 0)); break;
                    case GLFW_RELEASE: Data->eventQueue->add(CreateRef<KeyReleasedEvent>(_Key)); break;
                    case GLFW_REPEAT: Data->eventQueue->add(CreateRef<KeyPressedEvent>(_Key, 1)); break;
                }
            });

        glfwSetCharCallback(m_Window, [](GLFWwindow* _Window, uint32_t _KeyCode) {
            WindowData* Data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(_Window));
            Data->eventQueue->add(CreateRef<KeyTypedEvent>(_KeyCode));
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* _Window, int _Button, int _Action, int _Mods) {
            (void)_Mods;
            WindowData* Data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(_Window));
            switch (_Action) {
                case GLFW_PRESS: Data->eventQueue->add(CreateRef<MouseButtonPressedEvent>(_Button)); break;
                case GLFW_RELEASE: Data->eventQueue->add(CreateRef<MouseButtonReleasedEvent>(_Button)); break;
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* _Window, double _OffsetX, double _OffsetY) {
            WindowData* Data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(_Window));
            Data->eventQueue->add(
                CreateRef<MouseScrolledEvent>(static_cast<float>(_OffsetX), static_cast<float>(_OffsetY)));
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* _Window, double _PosX, double _PosY) {
            WindowData* Data = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(_Window));
            Data->eventQueue->add(
                CreateRef<MouseMovedEvent>(static_cast<float>(_PosX), static_cast<float>(_PosY)));
        });
    }

}    // namespace LM
