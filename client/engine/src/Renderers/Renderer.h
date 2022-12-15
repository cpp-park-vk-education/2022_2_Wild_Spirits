#pragma once

#include "RendererInterface.h"

namespace LM {

    class Renderer: public RendererInterface {
    public:
        Renderer();
        virtual ~Renderer() = default;
        virtual void onEvent(Ref<Event> event) override {}

        virtual void start(glm::uvec2 windowSize, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;

        virtual void pushTransform(const glm::mat4 transform) override;
        virtual void popTransform() override;

        virtual void draw(RenderableTexture* renderable) override;
        virtual void draw(RenderableGroupInterface* renderable) override;
    };

}
