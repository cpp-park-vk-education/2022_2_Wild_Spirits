#pragma once

#include <Events/Events.h>

namespace LM {

    class Renderer {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;
        virtual void onEvent(Ref<Event> event) = 0;
    };

}
