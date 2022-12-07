#include <Renderables/Gui/RenderableGuiGroup.h>

namespace LM {

    class RenderableBottomActionGroup : public RenderableGuiGroup {
    public:
        RenderableBottomActionGroup(
            float space = 5.0f, Vector<Ref<RenderableGui>> renderables = {}, const RenderableGuiProps& propsGui = { { RenderableGuiAlign::Align::kCenter } });

        virtual void rebuid(glm::uvec2 size) override;
        virtual glm::vec2 getSize() const override;
    protected:
        float m_Space;
    };

}
