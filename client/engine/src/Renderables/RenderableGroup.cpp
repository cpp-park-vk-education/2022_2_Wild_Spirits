#include "RenderableGroup.h"

namespace LM {

    void RenderableGroup::add(Ref<RenderableInterface> renderable) {
        m_Renderables.emplace_back(renderable);
    }

    void RenderableGroup::remove(size_t id) {
        m_Renderables.erase(m_Renderables.begin() + id);
    }

}
