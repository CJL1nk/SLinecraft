//
// Created by CJ on 3/25/26.
//

#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(const float fov, const float aspectRatio, const float near, const float far) {

    this->position = glm::vec3(0.0f, 10.0f, 0.0f);
    this->cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    this->cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);

    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->cameraFront = glm::normalize(this->cameraDirection);
    this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->cameraUp));

    this->view = glm::lookAt(position, position + cameraFront, cameraUp);
    this->projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void Camera::move(const glm::vec3& direction) {
    this->position += direction;
    this->view = glm::lookAt(this->position, this->position + this->cameraFront, this->cameraUp);
}

void Camera::rotate(float pitch, float yaw) {
    this->yaw += yaw;
    this->pitch += pitch;

    // Prevent camera flipping
    if (this->pitch > 89.0f) {
        this->pitch = 89.0f;
    }

    if (this->pitch < -89.0f) {
        this->pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cosf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));
    front.y = sinf(glm::radians(this->pitch));
    front.z = sinf(glm::radians(this->yaw)) * cosf(glm::radians(this->pitch));

    this->cameraFront = glm::normalize(front);
    this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->cameraUp));
    this->view = glm::lookAt(position, position + cameraFront, cameraUp);
}

glm::mat4 Camera::getProjection() const {
    return this->projection;
}

glm::mat4 Camera::getView() const {
    return this->view;
}

glm::vec3 Camera::getUp() const {
    return this->cameraUp;
}

glm::vec3 Camera::getFront() const {
    return this->cameraFront;
}

glm::vec3 Camera::getRight() const {
    return this->cameraRight;
}