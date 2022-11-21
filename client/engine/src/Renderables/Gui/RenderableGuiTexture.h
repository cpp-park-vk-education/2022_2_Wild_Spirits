#pragma once

#include "RenderableGui.h"
#include <Textures/Texture2D.h>
#include <Buffers/VertexArray.h>

namespace LM {

    class RenderableGuiTexture : public RenderableGui {
    public:
        RenderableGuiTexture(Ref<Texture2D> texture);
        virtual ~RenderableGuiTexture() = default;


        virtual void draw(RendererGui* renderer) override;
        virtual glm::uvec2 getSize() const override { return m_Texture->getSize(); }
    protected:
        Ref<VertexArray> m_VertexArray;
        Ref<Texture2D> m_Texture;
    };

}
