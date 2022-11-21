#pragma once

#include <cstdint>

#include <glm/glm.hpp>

#include <Actions/Action.h>

namespace LM {

    class UseAction : public Action {
    public:
        const inline glm::uvec2 getTarget() const { m_Target; }
        const inline glm::uvec2 getRange()  const { m_Range; }

        inline void setTarget(const glm::uvec2 target) { m_Target = target; }
    protected:
        glm::uvec2 m_Target;
        glm::uvec2 m_Range;
    };

}
