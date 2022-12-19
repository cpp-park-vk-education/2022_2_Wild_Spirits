#pragma once

#include <iostream>
#include <string>

#include <Core/Base.h>

namespace LM {

    enum class EventType {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

#define EVENT_CLASS_TYPE(type)                                                                               \
    static EventType getStaticType() { return EventType::type; }                                             \
    virtual EventType getEventType() const override { return getStaticType(); }                              \
    virtual const char* getName() const override { return #type; }

    class Event {
    public:
        virtual ~Event() = default;

        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual std::string toString() const { return getName(); }

        bool Handled = false;
    };

    inline std::ostream& operator<<(std::ostream& out, const Event& event) { return out << event.toString(); }

}    // namespace LM
