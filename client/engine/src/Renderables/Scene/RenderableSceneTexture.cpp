#include "RenderableSceneTexture.h"

#include <Renderers/Scene/RendererScene.h>

namespace LM {

    RenderableSceneTexture::RenderableSceneTexture(Ref<Texture2D> texture)
        : m_Texture(texture) 
    { 
    
    }

    void RenderableSceneTexture::draw(RendererScene* renderer) {

    }

}
