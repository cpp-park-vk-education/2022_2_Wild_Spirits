#pragma once

#include "RendererInterface.h"

namespace LM {

    class Renderer : public RendererInterface {
    public:
        Renderer();
        virtual ~Renderer() = default;
        virtual void onEvent(Ref<Event> event) override { }

        virtual void start() override;

        virtual void draw(RenderableTexture* renderable) override;
        virtual void draw(RenderableGroupInterface* renderable) override;
    };

}
