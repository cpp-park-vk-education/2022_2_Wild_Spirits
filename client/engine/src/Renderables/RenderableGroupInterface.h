#pragma once

#include <Transform/Transform.h>
#include <Core/Color.h>
#include <Events/Events.h>
#include <Utils/Timer.h>
#include "RenderableInterface.h"

namespace LM {

    class RenderableGroupInterface : virtual public RenderableInterface {
    public:
        RenderableGroupInterface() = default;
        virtual ~RenderableGroupInterface() = default;

        virtual void draw(RendererInterface* renderer) override;
        virtual Ref<RenderableInterface> getRenderable(size_t id) const = 0;
        virtual size_t getRenderablesCount() const = 0;
    };

}
