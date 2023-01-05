#pragma once

#include <queue>

#include "EventInterface.h"

namespace LM {

    class EventQueue {
    public:
        EventQueue() = default;

        void add(const Ref<Event>& event) { m_Events.push(event); }

        bool empty() const { return m_Events.empty(); }

        Ref<Event> pop() {
            Ref<Event> res = m_Events.front();
            m_Events.pop();
            return res;
        }

    protected:
        std::queue<Ref<Event>> m_Events;
    };

}    // namespace LM
