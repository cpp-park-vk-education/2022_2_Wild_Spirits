#pragma once

#include <glm/glm.hpp>

#include "Rotation.h"

namespace LM {

    struct Transform {

        glm::mat4 getMatrix() const;

        glm::vec2 position = glm::vec2(0.0f);
        Rotation rotation = Rotation(0.0f);
        glm::vec2 scale = glm::vec2(1.0f);
        float zIndex = 0.0f;
    };

}    // namespace LM
