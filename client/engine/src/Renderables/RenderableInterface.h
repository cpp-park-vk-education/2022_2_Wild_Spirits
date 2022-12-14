#pragma once

#include <Core/Color.h>
#include <Events/Events.h>
#include <Transform/Transform.h>
#include <Utils/ConsoleLog.h>
#include <Utils/Timer.h>

namespace LM {

    class RendererInterface;

    class RenderableInterface {
    public:
        RenderableInterface(const Transform& transform = Transform(), const Color& color = Color(1.0f))
            : m_Transform(transform),
              m_Color(color) { }
        virtual ~RenderableInterface() = default;

        inline const Transform& getTransform() const { return m_Transform; }
        inline void setTransform(const Transform& transform) { m_Transform = transform; }

        inline const Color& getColor() const { return m_Color; }
        inline void setColor(const Color& color) { m_Color = color; }

        virtual void onEvent(Ref<Event> event) { }
        virtual void onUpdate(Tick tick) { (void)tick; }

        virtual void draw(RendererInterface* renderer) = 0;

    protected:
        Transform m_Transform;
        Color m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    };

}    // namespace LM
