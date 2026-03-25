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


class Object {

    public:
        Object(const float* vertices, const glm::vec3& worldPos, const std::shared_ptr<Texture>& texture) :
            vertices(vertices), worldPos(worldPos), modelMatrix(glm::mat4(1.0f)), texture(texture) {
            this->modelMatrix = glm::translate(this->modelMatrix, worldPos);
        }

        void rotate(const float& degrees, const glm::vec3& axis);

        void render(const Camera& camera);

        [[nodiscard]] glm::mat4 getModelMatrix() const;

        [[nodiscard]] Texture* getTexture() const;

    private:
        const float* vertices;

        glm::vec3 worldPos;
        glm::vec4 rotation{}; // (degrees, x, y, z)
        float scale{};

        glm::mat4 modelMatrix; // Contains transformed vertices

        std::shared_ptr<Texture> texture;
};


#endif //SLINECRAFT_OBJECT_H