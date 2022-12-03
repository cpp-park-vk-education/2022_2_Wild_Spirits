#pragma once

#include <Renderables/RenderableTexture.h>

namespace LM {

    class RenderableTile : public RenderableTexture {
    public:
        RenderableTile(Ref<Texture2D> texture) : RenderableTexture(texture) { }
        virtual ~RenderableTile() = default;

        virtual void onEvent(Ref<Event> event) override;
    };

}
