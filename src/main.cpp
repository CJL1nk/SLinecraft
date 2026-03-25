//
// Created by CJ on 3/2/26.
//

#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>

#include "./engine/Object.h"
#include "./engine/render/glm/gtc/type_ptr.hpp"
#include "./engine/render/glad/include/glad/glad.h"

#include "./engine/render/window.h"
#include "./engine/render/shaders/shaders.h"
#include "./engine/render/Texture.h"
#include "./engine/render/Shader.h"
#include "./engine/render/ShaderProgram.h"
#include "./engine/render/Camera.h"

int main() {

    constexpr uint16_t SCREEN_WIDTH = 800;
    constexpr uint16_t SCREEN_HEIGHT = 800;
    constexpr float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    constexpr float FOV = glm::radians(60.0f);

    SDL_Window* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Slinecraft");

    Camera camera(FOV, ASPECT_RATIO, 0.1f, 100.0f);
    camera.move(glm::vec3(0.0f, 0.0f, -3.0f));

    SDL_GL_SetSwapInterval(1);

    // Textures and Shaders ---------------------------------------------------------------------------------
    std::shared_ptr<Texture> texture1 = std::make_shared<Texture>("../textures/tex.png", GL_RGB);
    texture1->load();

    glActiveTexture(GL_TEXTURE0);
    texture1->bind();

    Shader vertexShader(vertexShaderSource, GL_VERTEX_SHADER);
    Shader fragmentShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    vertexShader.compile();
    fragmentShader.compile();

    ShaderProgram program;
    program.add(vertexShader);
    program.add(fragmentShader);
    program.link();
    program.use();

    glUniform1i(glGetUniformLocation(program.getHandle(), "texture1"), 0); // set it manually

    vertexShader.deleteShader();
    fragmentShader.deleteShader();
    // ------------------------------------------------------------------------------------------------------

    std::vector<Object> objects;
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    objects.emplace_back(vertices, glm::vec3( 0.0f,  0.0f,  0.0f), texture1);
    objects.emplace_back(vertices, glm::vec3( 2.0f,  5.0f, -15.0f), texture1);
    objects.emplace_back(vertices, glm::vec3(-1.5f, -2.2f, -2.5f), texture1);
    objects.emplace_back(vertices, glm::vec3(-3.8f, -2.0f, -12.3f), texture1);
    objects.emplace_back(vertices, glm::vec3( 2.4f, -0.4f, -3.5f), texture1);
    objects.emplace_back(vertices, glm::vec3(-1.7f,  3.0f, -7.5f), texture1);
    objects.emplace_back(vertices, glm::vec3( 1.3f, -2.0f, -2.5f), texture1);
    objects.emplace_back(vertices, glm::vec3( 1.5f,  2.0f, -2.5f), texture1);
    objects.emplace_back(vertices, glm::vec3( 1.5f,  0.2f, -1.5f), texture1);
    objects.emplace_back(vertices, glm::vec3(-1.3f,  1.0f, -1.5f), texture1);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    const int modelLoc = glGetUniformLocation(program.getHandle(), "model");
    const int projLoc = glGetUniformLocation(program.getHandle(), "projection");
    const int viewLoc = glGetUniformLocation(program.getHandle(), "view");

    // Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    bool quit = false;
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

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < objects.size(); i++) {
            Object& current = objects[i];

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(current.getModelMatrix()));

            current.rotate(0.02f, glm::vec3(0.5f, 1.0f, 0.0f));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    program.deleteProgram();
    texture1->deleteTexture();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
