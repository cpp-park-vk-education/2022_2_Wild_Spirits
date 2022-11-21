#pragma once

#include <Transform/Transform.h>
#include <Core/Color.h>
#include <Events/Events.h>
#include <Utils/Timer.h>

namespace LM {

    class Renderable {
    public:
        Renderable() = default;
        virtual ~Renderable() = default;

        const Transform& getTransform() const { return m_Transform; }
        void setTransform(const Transform& transform) { m_Transform = transform; }

        virtual void onEvent(Ref<Event> event) { }
        virtual void onUpdate(Tick tick) { }
    protected:
        Transform m_Transform;
        Color m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    };

}
