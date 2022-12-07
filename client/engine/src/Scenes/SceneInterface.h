#pragma once

#include <Events/Events.h>
#include <Utils/Timer.h>

namespace LM {

    class SceneInterface {
    public:
        SceneInterface() = default;
        virtual ~SceneInterface() = default;
        virtual void onEvent(Ref<Event> event) = 0;
        virtual void onUpdate(Tick tick) = 0;

        virtual void render() = 0;
    };

}
