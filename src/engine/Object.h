//
// Created by CJ on 3/11/26.
//

#ifndef SLINECRAFT_OBJECT_H
#define SLINECRAFT_OBJECT_H

#include "./render/glm/vec3.hpp"
#include "./render/Texture.h"


class Object {

    public:
        Object(const float* vertices, glm::vec3 worldPos, Texture& texture) : vertices(vertices), worldPos(worldPos), texture(&texture){}

    private:
        const float* vertices;
        glm::vec3 worldPos;
        Texture* texture;
};


#endif //SLINECRAFT_OBJECT_H