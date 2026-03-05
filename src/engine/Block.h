//
// Created by CJ on 3/2/26.
//

#ifndef SLINECRAFT_BLOCK_H
#define SLINECRAFT_BLOCK_H

#include "types.h"

/**
 * (To be) Abstract class representing a generic block, cannot be instantiated.
 */
class Block {

    public:
        explicit Block(const Position& p);
        Position pos;
        int hardness;
};


#endif //SLINECRAFT_BLOCK_H