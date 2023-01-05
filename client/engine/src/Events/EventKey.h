#pragma once

#include "EventInterface.h"
#include <Core/KeyCode.h>

namespace LM {

    class KeyEvent : public Event {
    public:
        KeyCode getKeyCode() const { return m_KeyCode; }

    protected:
        KeyEvent(KeyCode keyCode) : m_KeyCode(keyCode) { }

    protected:
        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(KeyCode keyCode, uint16_t repeatCount)
            : KeyEvent(keyCode),
              m_RepeatCount(repeatCount) { }

        uint16_t getRepeatCount() const { return m_RepeatCount; }

        std::string toString() const override {
            return "KeyPressedEvent: " + std::to_string(m_KeyCode) + ", " + std::to_string(m_RepeatCount) +
                   " repeats";
        }

        EVENT_CLASS_TYPE(KeyPressed)
    protected:
        uint16_t m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(KeyCode keyCode) : KeyEvent(keyCode) { }

        std::string toString() const override { return "KeyReleasedEvent: " + std::to_string(m_KeyCode); }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(KeyCode keyCode) : KeyEvent(keyCode) { }

        std::string toString() const override { return "KeyTypedEvent: " + std::to_string(m_KeyCode); }

        EVENT_CLASS_TYPE(KeyTyped)
    };

}    // namespace LM
