#pragma once

#include "RenderableGui.h"
#include <Renderables/RenderableTexture.h>
#include <Textures/Texture2D.h>
#include <Buffers/VertexArray.h>

namespace LM {

    class RenderableGuiTexture: public RenderableGui {
    public:
        RenderableGuiTexture(const RenderableTextureProps& propsTexture, const RenderableGuiProps& propsGui = {});
        virtual ~RenderableGuiTexture() = default;

        void setTransform(const Transform& transform) { m_Renderable->setTransform(transform); }
        void setColor(const Color& color) { m_Renderable->setColor(color); }

        virtual void onUpdate(Tick tick) override;

        virtual glm::vec2 getSize() const override {
            glm::uvec2 texSize = m_Renderable->getSize();
            glm::vec2 renderableSize = m_Renderable->getTransform().scale;
            return glm::vec2(renderableSize.x * texSize.x, renderableSize.y * texSize.y);
        }
        virtual void draw(RendererInterface* renderer) override;
    protected:
        Scope<RenderableTexture> m_Renderable;
    };

}
