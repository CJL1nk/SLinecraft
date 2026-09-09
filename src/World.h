//
// Created by CJ on 5/16/26.
//

#ifndef SLINECRAFT_WORLD_H
#define SLINECRAFT_WORLD_H

#include <vector>

#include "Block.h"

/**
 * Does nothing except return a vector of blocks, currently
 */
class World {

    public:
        /**
         * Initializes and generates a new world
         * @param seed Random seed to generate world with (currently does nothing)
         */
        explicit World(const int seed) : seed(seed) { generateWorld(); };

        /**
         * Adds a block into the world
         * @param block Block to add
         */
        void addBlock(const Block& block);

        /**
         * Returns a pointer to the world block vector
         * @return Pointer to the world block vector
         */
        std::vector<Block>* getBlocks();

    private:
        int seed;
        std::vector<Block> blocks;

        /**
         * Returns an array of blocks
         * @return An array of blocks
         */
        void generateWorld();
};


#endif //SLINECRAFT_WORLD_H