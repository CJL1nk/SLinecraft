//
// Created by CJ on 5/16/26.
//

#include "World.h"

#include <iostream>

void World::addBlock(const Block& block) {
    this->blocks.emplace_back(block);
}

std::vector<Block>* World::getBlocks() {
    return &this->blocks;
}


void World::generateWorld() {

    int totalBlocks = 0;
    std::vector<Block> blocks;

    for (int x = -50; x <= 50; x++) {
        for (int z = -50; z <= 50; z++) {
            int blockID = 0;
            float y = 1;

            if (x % 10 == 0 && z % 10 == 0) {
                y = 4;
            }

            if (abs(x) >= 37) {
                y = ceil(sin((float)x / 2.0f) * sin((float)z / 2.0f) * 4.0f + 4);
                blockID = 1;
            } else if (z % 10 == 0 || x % 10 == 0) {


                blocks.emplace_back(glm::vec3(x, 4, z), 1);
            }

            for (int i = 0; i < y; i++) {
                blocks.emplace_back(glm::vec3(x, i, z), blockID);
                totalBlocks++;
            }
        }
    }

    std::cout << "Generated world with " << totalBlocks << " blocks" << std::endl;
    this->blocks = blocks;
}
