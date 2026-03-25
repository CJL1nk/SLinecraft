//
// Created by CJ on 3/25/26.
//

#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(const float fov, const float aspectRatio, const float near, const float far) {
    this->projection = glm::perspective(fov, aspectRatio, near, far);
    this->view = glm::mat4(1.0f);
}

void Camera::move(const glm::vec3& direction) {
    this->position += direction;
    this->view = glm::translate(this->view, direction);
}

glm::mat4 Camera::getProjection() const {
    return this->projection;
}

glm::mat4 Camera::getView() const {
    return this->view;
}