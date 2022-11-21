#pragma once

#include <Events/Events.h>

namespace LM {

    class Scene {
    public:
        Scene() = default;
        virtual ~Scene() = default;
        virtual void onEvent(Ref<Event> event) = 0;

        virtual void render() = 0;
    };

}
