#pragma once

#include <Renderables/Renderable.h>

namespace LM {

    class RendererScene;

    class RenderableScene : Renderable {
    public:
        RenderableScene() = default;
        virtual ~RenderableScene() = default;

        virtual void draw(RendererScene* renderer) = 0;
    protected:
    };

}
