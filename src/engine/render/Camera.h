//
// Created by CJ on 3/25/26.
//

#ifndef SLINECRAFT_CAMERA_H
#define SLINECRAFT_CAMERA_H

#include "./glm/glm.hpp"


class Camera {

    public:
        Camera(float fov, float aspectRatio, float near, float far);

        void move(const glm::vec3& direction);

        [[nodiscard]] glm::mat4 getProjection() const;
        [[nodiscard]] glm::mat4 getView() const;

    private:
        glm::mat4 projection;
        glm::mat4 view;

        glm::vec3 position;
};


#endif //SLINECRAFT_CAMERA_H