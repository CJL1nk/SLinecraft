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
        int seed; //

        /**
         * Returns an array of blocks
         * @return An array of blocks
         */
        static std::vector<Block> generateWorld();
};


#endif //SLINECRAFT_WORLD_H