//
// Created by CJ on 3/11/26.
//

#ifndef SLINECRAFT_OBJECT_H
#define SLINECRAFT_OBJECT_H

#include "./render/glm/glm.hpp"
#include "./render/Texture.h"
#include "render/glm/fwd.hpp"


class Object {

    public:
        Object(const float* vertices, const glm::vec3& worldPos, const Texture texture) :
            vertices(vertices), worldPos(worldPos), modelMatrix(glm::mat4(1.0f)), texture(texture){}

        void rotate(float degrees, glm::vec3 axis);

        void render();

        [[nodiscard]] glm::mat4 getModelMatrix() const;

    private:
        const float* vertices;

        glm::vec3 worldPos;
        glm::vec4 rotation{}; // (Degrees, x, y, z)
        float scale{};

        glm::mat4 modelMatrix; // Contains transformed vertices

        Texture texture;
};


#endif //SLINECRAFT_OBJECT_H