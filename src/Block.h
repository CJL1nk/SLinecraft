//
// Created by CJ on 5/27/26.
//

#ifndef SLINECRAFT_BLOCK_H
#define SLINECRAFT_BLOCK_H

#include "./engine/Object.h"
#include "./blockdefs.h"

/**
 * Class representing an in-game block. Every block has set static vertices, a cube composed of vertices from -0.5 to 0.5 in all axis.
 */
class Block : public Object {
    public:
    /**
     * Default constructor, initializes an Object with static vertices
     * @param worldPos World position
     * @param blockID Block ID
     */
    Block(const glm::vec3& worldPos, const int blockID) : Object(vertices.data(), vertices.size(), worldPos, nullptr) {
        this->blockID = blockID;

        switch (blockID) {
            case DIRT_BLOCK: {this->texture = dirtTexture; break;}
            case STONE_BLOCK: {this->texture = stoneTexture; break;}
        }
    };

    /**
     * Loads all block textures into memory, shouldn't be HERE in this class but it's here for now
     */
    static void initBlockTextures();

    private:

        int blockID; // Determines texture, hardness, and other block properties
        glm::vec3 blockPos;

        // LOOOOOL
        static inline const std::array<float, 288> vertices = {
            // positions          // texcoords  // normals

            // back face
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,

            // front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,

            // left face
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,

            // right face
             0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,

            // bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,

            // top face
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f, 1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 1.0f,  0.0f
        };
};

#endif //SLINECRAFT_BLOCK_H