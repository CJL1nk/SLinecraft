//
// Created by CJ on 3/2/26.
//
#include "./engine/event.h"
#include "./engine/Engine.h"


int main() {

    Engine* engine = new Engine();

    while (!quit) {
        pollEvents();
        engine->update(); 
        engine->render();
    }

    return 0;
}
