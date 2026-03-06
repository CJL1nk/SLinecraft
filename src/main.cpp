//
// Created by CJ on 3/2/26.
//

#include <cstdint>
#include <SDL3/SDL.h>

#include "./engine/render/glad/include/glad/glad.h"
#include "engine/render/window.h"
#include "engine/render/shaders/shaders.h"

int main() {

    constexpr uint16_t SCREEN_WIDTH = 800;
    constexpr uint16_t SCREEN_HEIGHT = 800;
    bool quit = false;

    SDL_Window* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Slinecraft");

    SDL_GL_SetSwapInterval(1);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    while (!quit) {

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
                }
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
