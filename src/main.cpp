//
// Created by CJ on 3/2/26.
//

#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>

#include "./engine/render/glm/glm.hpp"
#include "./engine/render/glm/gtc/matrix_transform.hpp"
#include "./engine/render/glm/gtc/type_ptr.hpp"

#include "./engine/render/glad/include/glad/glad.h"
#include "./engine/render/window.h"
#include "./engine/render/shaders/shaders.h"
#include "./engine/render/Texture.h"
#include "./engine/render/Shader.h"
#include "./engine/render/ShaderProgram.h"

int main() {

    constexpr uint16_t SCREEN_WIDTH = 800;
    constexpr uint16_t SCREEN_HEIGHT = 800;
    bool quit = false;

    SDL_Window* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Slinecraft");

    SDL_GL_SetSwapInterval(1);

    constexpr float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
   };
    const unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    float degs = 1.f;

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(degs), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(1.5, 1.5, 0.5));

    Shader vertexShader(vertexShaderSource, GL_VERTEX_SHADER);
    Shader fragmentShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    vertexShader.compile();
    fragmentShader.compile();

    ShaderProgram program;
    program.add(&vertexShader);
    program.add(&fragmentShader);
    program.link();
    program.use();

    vertexShader.deleteShader();
    fragmentShader.deleteShader();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Texutre
    Texture texture1("../textures/tex.png", GL_RGB);
    texture1.load();

    glActiveTexture(GL_TEXTURE0);
    texture1.bind();

    glUniform1i(glGetUniformLocation(program.getHandle(), "texture1"), 0); // set it manually

    const unsigned int transformLoc = glGetUniformLocation(program.getHandle(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    // Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
                    if (event.key.key == SDLK_R) {
                        break;
                    }
                }
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        program.use();

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        trans = glm::rotate(trans, glm::radians(degs), glm::vec3(0.0, 0.0, 1.0));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    program.deleteProgram();
    texture1.deleteTexture();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
