//
// Created by CJ on 3/25/26.
//

#ifndef SLINECRAFT_CAMERA_H
#define SLINECRAFT_CAMERA_H

#include "./glm/glm.hpp"

/**
 * Class representing an in-game camera
 */
class Camera {

    public:
        /**
         * Default constructor
         * @param fov Field of view (degrees) of camera to be initialized
         * @param aspectRatio Screem aspect ratio (width/height)
         * @param near Minimum distance of object to be rendered
         * @param far Maximum distance of object to be rendered
         */
        Camera(float fov, float aspectRatio, float near, float far);

        /**
         * Moves the camera in some specified direction vector.
         * Adds the direction vector to camera position
         * @param direction Direction to move camera
         */
        void move(const glm::vec3& direction);

        /**
         * Rotates the camera with a given pitch and yaw
         * @param pitch Degrees to pitch camera
         * @param yaw Degrees to yaw camera
         */
        void rotate(float pitch, float yaw);

        /**
         * Returns camera projection
         * @return Camera projection
         */
        [[nodiscard]] glm::mat4 getProjection() const;
        /**
         * Returns camera view
         * @return Camera view
         */
        [[nodiscard]] glm::mat4 getView() const;
        /**
         * Returns camera front vector
         * @return Camera front vector
         */
        [[nodiscard]] glm::vec3 getFront() const;
        /**
         * Returns camera right vector
         * @return Camera right vector
         */
        [[nodiscard]] glm::vec3 getRight() const;


    private:
        glm::vec3 position;

        float yaw = -90.0f;
        float pitch = 0.0f;
        glm::vec3 rotation;

        glm::mat4 view;
        glm::mat4 projection;

        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;

        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
        glm::vec3 cameraFront;
};


#endif //SLINECRAFT_CAMERA_H