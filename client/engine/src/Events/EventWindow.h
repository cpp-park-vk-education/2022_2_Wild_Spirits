#pragma once

#include "EventInterface.h"

#include <string>

namespace LM {

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) { }

        inline uint32_t getWidth() const { return m_Width; }
        inline uint32_t getHeight() const { return m_Height; }

        std::string toString() const override {
            return "WindowResizeEvent: " + std::to_string(m_Width) + " : " + std::to_string(m_Height);
        }

        EVENT_CLASS_TYPE(WindowResize)
    protected:
        uint32_t m_Width;
        uint32_t m_Height;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowDropEvent : public Event {
    public:
        WindowDropEvent(int count, const char* paths[]) {
            for (int i = 0; i < count; ++i) {
                m_Paths.emplace_back(paths[i]);
            }
        }

        const std::vector<std::string> getPaths() const { return m_Paths; }

        std::string toString() const override {
            std::string res = "WindowDropEvent: {";
            for (const auto& str : m_Paths) {
                res += str + "; ";
            }
            return res + "}";
        }

        EVENT_CLASS_TYPE(WindowDrop)
    protected:
        std::vector<std::string> m_Paths;
    };

}    // namespace LM
