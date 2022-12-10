#include "RenderableGroupInterface.h"

#include <Renderers/RendererInterface.h>

namespace LM {

    void RenderableGroupInterface::draw(RendererInterface* renderer) {
        for (auto& renderable : getRenderables()) {
            renderable->draw(renderer);
        }
    }

}
