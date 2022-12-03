#pragma once

#include <Events/Events.h>
#include <Shader/Shader.h>

namespace LM {

    class RenderableTexture;
    class RenderableGroupInterface;

    class RendererInterface {
    public:
        RendererInterface() = default;
        virtual ~RendererInterface() = default;
        virtual void onEvent(Ref<Event> event) = 0;

        virtual void start() = 0;

        virtual void draw(RenderableTexture* renderable) = 0;
        virtual void draw(RenderableGroupInterface* renderable) = 0;
    protected:
        Vector<glm::mat4> m_Transforms;
        Scope<Shader> m_Shader;
    };

}
