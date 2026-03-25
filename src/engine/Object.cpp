//
// Created by CJ on 3/11/26.
//

#include "Object.h"
#include "render/glm/ext/matrix_transform.hpp"

void Object::rotate(const float& degrees, const glm::vec3& axis) {
    this->rotation = glm::vec4(degrees, axis); // Will change this later to be a bit better
    this->modelMatrix = glm::rotate(this->modelMatrix, degrees, axis);
}


void Object::render(const Camera& camera) {

}

glm::mat4 Object::getModelMatrix() const {
    return this->modelMatrix;
}

