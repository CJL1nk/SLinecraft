//
// Created by CJ on 3/11/26.
//

#ifndef SLINECRAFT_OBJECT_H
#define SLINECRAFT_OBJECT_H

#include <memory>

#include "./render/glm/glm.hpp"
#include "./render/Texture.h"
#include "./render/Camera.h"
#include "./render/glm/fwd.hpp"
#include "render/glm/ext/matrix_transform.hpp"

/**
 * Unfinished class
 */
class Object {

    public:
        /**
         * Default constructor, creates a new object
         * @param vertices Pointer to array of vertices
         * @param vertexCount Number of vertices
         * @param worldPos Default world position
         * @param texture Shared pointer to object texture
         */
        Object(const float* vertices, const int vertexCount, const glm::vec3& worldPos, const std::shared_ptr<Texture>& texture) :
            vertices(vertices), vertexCount(vertexCount), worldPos(worldPos), modelMatrix(glm::mat4(1.0f)), texture(texture) {
            this->modelMatrix = glm::translate(this->modelMatrix, worldPos);
        }

        /**
         * Rotates an object n degrees around a specified axis
         * @param degrees Number of degrees to rotate
         * @param axis Axis vector
         */
        void rotate(const float& degrees, const glm::vec3& axis);

        /**
         * I don't know yet
         * @param camera hi
         */
        void render(const Camera& camera);

        /**
         * Returns the model matrix of the object
         * @return Model matrix of the object
         */
        [[nodiscard]] glm::mat4 getModelMatrix() const;
        /**
         * Returns a shared pointer to the object's texture
         * @return Shared pointer to the object's texture
         */
        [[nodiscard]] std::shared_ptr<Texture> getTexture() const;
        /**
         * Returns the object's array of vertices
         * @return Array of object's vertices
         */
        [[nodiscard]] const float* getVertices() const;
        /**
         * Returns the vertex count of the object
         * @return Object vertex count
         */
        [[nodiscard]] int getVertexCount() const;

    protected:
        const float* vertices;
        int vertexCount;
        std::shared_ptr<Texture> texture;

    private:
        glm::vec3 worldPos;
        glm::vec4 rotation{}; // (degrees, x, y, z)
        float scale{};

        glm::mat4 modelMatrix; // Contains transformed vertices

        float emissivity;
};


#endif //SLINECRAFT_OBJECT_H