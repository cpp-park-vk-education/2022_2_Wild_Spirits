#pragma once

#include <Events/Events.h>

namespace LM {

    class SceneInterface {
    public:
        SceneInterface() = default;
        virtual ~SceneInterface() = default;
        virtual void onEvent(Ref<Event> event) = 0;

        virtual void render();
    };

}
