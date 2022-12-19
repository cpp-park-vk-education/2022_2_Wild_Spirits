#pragma once

#include "EventInterface.h"
#include <Core/MouseCode.h>

namespace LM {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) { }

        float getX() const { return m_MouseX; }
        float getY() const { return m_MouseY; }

        std::string toString() const override {
            return "MouseMovedEvent: " + std::to_string(m_MouseX) + ", " + std::to_string(m_MouseY);
        }

        EVENT_CLASS_TYPE(MouseMoved)
    protected:
        float m_MouseX;
        float m_MouseY;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float offsetX, float offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) { }

        float getOffsetX() const { return m_OffsetX; }
        float getOffsetY() const { return m_OffsetY; }

        std::string toString() const override {
            return "MouseScrolledEvent: " + std::to_string(m_OffsetX) + ", " + std::to_string(m_OffsetY);
        }

        EVENT_CLASS_TYPE(MouseScrolled)
    protected:
        float m_OffsetX;
        float m_OffsetY;
    };

    class MouseButtonEvent : public Event {
    public:
        MouseCode getMouseButton() const { return m_MouseButton; }

    protected:
        MouseButtonEvent(MouseCode mouseButton) : m_MouseButton(mouseButton) { }

    protected:
        MouseCode m_MouseButton;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(MouseCode mouseButton) : MouseButtonEvent(mouseButton) { }

        std::string toString() const override {
            return "MouseButtonPressedEvent: " + std::to_string(m_MouseButton);
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(MouseCode mouseButton) : MouseButtonEvent(mouseButton) { }

        std::string toString() const override {
            return "MouseButtonReleasedEvent: " + std::to_string(m_MouseButton);
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

}    // namespace LM
