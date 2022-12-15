#include "RenderableGuiTexture.h"

#include <Renderers/RendererInterface.h>

namespace LM {

    RenderableGuiTexture::RenderableGuiTexture(
        const RenderableTextureProps& propsTexture,
        const RenderableGuiProps& propsGui)
        : RenderableGui(propsGui),
        m_Renderable(CreateScope<RenderableTexture>(propsTexture)) {
    }

    void RenderableGuiTexture::onUpdate(Tick tick) {
        (void)tick;
    }


    void RenderableGuiTexture::draw(RendererInterface* renderer) {
        renderer->draw(m_Renderable.get());
    }

}    // namespace LM
