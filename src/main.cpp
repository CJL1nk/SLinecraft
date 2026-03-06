//
// Created by CJ on 3/2/26.
//

#include <cmath>
#include <iostream>
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
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   };
    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };

    const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    const unsigned int shaderProgram = createShaderProgram(2, vertexShader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

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

        float timeValue = SDL_GetTicks() / 100.f;
        float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
