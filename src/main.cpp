//
// Created by CJ on 3/2/26.
//
#include "./engine/event.h"
#include "./engine/Engine.h"


int main() {

    Engine* engine = new Engine();

    while (!quit) {
        engine->update();
    }
/*
    // Delete all textures when done with them please!!!!!!!!!!!!
    for (int i = 0; i < blocks.size(); i++) {
        Object& current = blocks[i];
        current.getTexture()->deleteTexture();
    }

    program.deleteProgram();
    SDL_DestroyWindow(window);
    SDL_Quit();
*/
    return 0;
}
