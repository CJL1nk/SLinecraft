//
// Created by CJ on 5/27/26.
//

#include "Block.h"

void Block::initBlockTextures() {
    dirtTexture->load();
    stoneTexture->load();
}

void Block::setEmission(const float emission) {
    this->emission = emission;
}
