#pragma once

#include <glm/glm.hpp>

#include "Rotation.h"

namespace LM {

    struct Transform {
        
        glm::mat4 getTransform();

        glm::vec2 position = glm::vec2(0.0f);
        Rotation rotation = Rotation(0.0f);
        glm::vec2 Scale = glm::vec2(1.0f);
        float zIndex = 0.0f;
    };

}
