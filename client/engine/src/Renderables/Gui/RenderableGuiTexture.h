#pragma once

#include "RenderableGui.h"
#include <Renderables/RenderableTexture.h>
#include <Textures/Texture2D.h>
#include <Buffers/VertexArray.h>

namespace LM {

    class RenderableGuiTexture : public RenderableGui, public RenderableTexture {
    public:
        RenderableGuiTexture(Ref<Texture2D> texture);
        virtual ~RenderableGuiTexture() = default;

        virtual glm::uvec2 getSize() const override { return m_Texture->getSize(); }
    };

}
