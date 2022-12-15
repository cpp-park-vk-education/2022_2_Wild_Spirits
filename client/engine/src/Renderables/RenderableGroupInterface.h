#pragma once

#include <Transform/Transform.h>
#include <Core/Color.h>
#include <Events/Events.h>
#include <Utils/Timer.h>
#include "RenderableInterface.h"

namespace LM {

    class RenderableGroupInterface: public RenderableInterface {
    public:
        RenderableGroupInterface(const Transform& transform = Transform()): RenderableInterface(transform) {}
        virtual ~RenderableGroupInterface() = default;

        virtual void draw(RendererInterface* renderer);
        virtual Ref<RenderableInterface> getRenderable(size_t id) const = 0;
        virtual size_t getRenderablesCount() const = 0;
    protected:
        virtual Vector<Ref<RenderableInterface>> getRenderables() = 0;
    };

}    // namespace LM
