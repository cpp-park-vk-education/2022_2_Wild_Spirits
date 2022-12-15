#pragma once

#include <Core/Base.h>
#include "EventInterface.h"

namespace LM {

    class EventDispatcher {
    public:
        EventDispatcher(Ref<Event> event): m_Event(event) {}

        template<typename T, typename F>
        bool dispatch(const F& func) {
            if (m_Event->getEventType() == T::getStaticType()) {
                m_Event->Handled = func(StaticRefCast<T>(m_Event));
                return true;
            }
            return false;
        }
    protected:
        Ref<Event> m_Event;
    };

}    // namespace LM
