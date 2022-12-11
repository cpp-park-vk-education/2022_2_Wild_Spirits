#pragma once

#include <Renderables/Gui/RenderableGuiGroup.h>
#include "RenderableBottomAction.h"

namespace LM {

    class RenderableBottomActionGroup : public RenderableGuiGroup {
    public:
        RenderableBottomActionGroup(float space = 5.0f, const RenderableGuiProps& propsGui = { { RenderableGuiAlign::Align::kCenter } });

        void add(Ref<RenderableBottomAction> renderable);

        Ref<UseAction> getAction();

        void setFocus();
        void setUnFocus();

        virtual void rebuid(glm::uvec2 size) override;
        virtual glm::vec2 getSize() const override;
    protected:
        float m_Space;
        Vector<Ref<RenderableBottomAction>> m_Items;
    };

}
