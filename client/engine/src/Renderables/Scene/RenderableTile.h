#pragma once

#include <Renderables/RenderableTexture.h>

namespace LM {

    class RenderableTile : public RenderableTexture {
    public:
        explicit RenderableTile(const RenderableTextureProps& props);
        virtual ~RenderableTile() = default;

        virtual void onEvent(Ref<Event> event) override;

    protected:
        bool m_IsHovered = false;
    };

}    // namespace LM
