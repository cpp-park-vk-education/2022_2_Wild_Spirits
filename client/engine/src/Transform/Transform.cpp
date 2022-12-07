#include "Transform.h"

#include <glm/gtx/transform.hpp>

namespace LM {

    glm::mat4 Transform::getMatrix() const {
        glm::mat4 posTransform = glm::translate(glm::vec3(position, zIndex));
        glm::mat4 rotTransform = glm::rotate(glm::radians(rotation()), glm::vec3(0.0f, 0.0f, -1.0f));
        glm::mat4 sclTransform = glm::scale(glm::vec3(scale, 0.0f));

        return posTransform * rotTransform * sclTransform;
    }

}
