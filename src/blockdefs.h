//
// Created by CJ on 5/27/26.
//

#ifndef SLINECRAFT_BLOCKDEFS_H
#define SLINECRAFT_BLOCKDEFS_H

#include "Block.h"
#include "./engine/render/glad/include/glad/glad.h"

#define DIRT_BLOCK 0
#define STONE_BLOCK 1

inline std::shared_ptr<Texture> dirtTexture = std::make_shared<Texture>("../textures/dirt.png", GL_RGB);
inline std::shared_ptr<Texture> stoneTexture = std::make_shared<Texture>("../textures/stone.png", GL_RGBA);

void initBlocks();

#endif //SLINECRAFT_BLOCKDEFS_H