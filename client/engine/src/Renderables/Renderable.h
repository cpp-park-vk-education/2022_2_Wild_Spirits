#pragma once

#include "RenderableInterface.h"
#include <Core/Color.h>

namespace LM {

    class Renderable: public RenderableInterface {
    public:
        struct Vertex
        {
            glm::vec3 position;
            glm::vec2 texCoord;
        };
    public:
        Renderable(Transform transform = Transform(), const Color& color = Color(1.0f))
            : RenderableInterface(transform, color) {
        }

        virtual ~Renderable() = default;
    };

}
