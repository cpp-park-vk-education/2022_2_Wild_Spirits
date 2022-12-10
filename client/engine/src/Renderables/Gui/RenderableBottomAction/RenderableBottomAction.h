#pragma once

#include <Renderables/Gui/RenderableGuiTexture.h>
#include <Actions/UseActions.h>

namespace LM {

    class RenderableBottomAction : public RenderableGuiTexture {
    public:
        RenderableBottomAction(const RenderableTextureProps& props);

        virtual void onEvent(Ref<Event> event) override;
        virtual void onUpdate(Tick tick) override;

        virtual Ref<UseAction> createUseAction(size_t actionId) const = 0;
    protected:
    };

}
