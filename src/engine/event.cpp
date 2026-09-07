//
// Created by CJ on 5/27/26.
//

#include "event.h"

#include <SDL3/SDL.h>

struct KeyPressMap {
    uint64_t keys;
};

void pollEvents() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_EVENT_QUIT) {
            quit = true;
        }

        switch (event.type) {
            case (SDL_EVENT_KEY_DOWN): {
                if (event.key.key == SDLK_Q) {
                    quit = true;
                    break;
                }
                if (event.key.key == SDLK_W) {
                    W = true;
                }
                if (event.key.key == SDLK_S) {
                    S = true;
                }
                if (event.key.key == SDLK_A) {
                    A = true;
                }
                if (event.key.key == SDLK_D) {
                    D = true;
                }
                if (event.key.key == SDLK_P) {
                    P = true;
                }
                if (event.key.key == SDLK_SPACE) {
                    SPACE = true;
                }
                if (event.key.key == SDLK_LCTRL) {
                    LCTRL = true;
                }
                if (event.key.key == SDLK_RIGHT) {
                    RIGHT = true;
                }
                if (event.key.key == SDLK_LEFT) {
                    LEFT = true;
                }
                if (event.key.key == SDLK_UP) {
                    UP = true;
                }
                if (event.key.key == SDLK_DOWN) {
                    DOWN = true;
                }
                break;
            }
            case (SDL_EVENT_KEY_UP): {
                if (event.key.key == SDLK_W) {
                    W = false;
                }
                if (event.key.key == SDLK_S) {
                    S = false;
                }
                if (event.key.key == SDLK_A) {
                    A = false;
                }
                if (event.key.key == SDLK_D) {
                    D = false;
                }
                if (event.key.key == SDLK_P) {
                    P = false;
                }
                if (event.key.key == SDLK_SPACE) {
                    SPACE = false;
                }
                if (event.key.key == SDLK_LCTRL) {
                    LCTRL = false;
                }
                if (event.key.key == SDLK_RIGHT) {
                    RIGHT = false;
                }
                if (event.key.key == SDLK_LEFT) {
                    LEFT = false;
                }
                if (event.key.key == SDLK_UP) {
                    UP = false;
                }
                if (event.key.key == SDLK_DOWN) {
                    DOWN = false;
                }
                break;
            }
        case (SDL_EVENT_MOUSE_MOTION): {
                mouseX = event.motion.xrel;
                mouseY = event.motion.yrel;
            }
            break;
        }
    }
}