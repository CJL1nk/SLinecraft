//
// Created by CJ on 3/2/26.
//

#include "includes.h"

int main() {

    constexpr Position p = {50.f, 50.f, 100.f, 0.0f, 0.0f, 0.0f};

    Block* b = new Block(p);
    b->hardness = 10000003;

    std::cout<< "Block pos: x" << b->pos.x << " y" << b->pos.y << " z" << b->pos.z << std::endl;

    SDL_Init(SDL_INIT_VIDEO);

    delete b;

    SDL_Quit();

    return 0;
}
