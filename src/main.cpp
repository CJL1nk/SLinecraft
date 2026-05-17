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
    constexpr float FOV = 60.0f; // Degrees

    SDL_Window* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Slinecraft");

    Camera camera(FOV, ASPECT_RATIO, 0.1f, 100.0f);
    const float cameraSpeed = 0.05f;

    camera.move(glm::vec3(0.0f, 0.0f, -3.0f));

    signed long int deltaTime = 0;
    signed long int  lastFrame = 0;

    SDL_GL_SetSwapInterval(1);

    // Textures and Shaders ---------------------------------------------------------------------------------
    std::shared_ptr<Texture> texture1 = std::make_shared<Texture>("../textures/dirt.png", GL_RGB);
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

    for (int x = -50; x <= 50; x++) {
        for (int z = -50; z <= 50; z++) {
            float y = sin((float)x / 2.0f) * sin((float)z / 2.0f) * 2.0f;
            objects.emplace_back(Object(vertices, glm::vec3(x, y, z), texture1));
        }
    }

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

    bool W = false;
    bool S = false;
    bool A = false;
    bool D = false;
    bool SPACE = false;
    bool LCTRL = false;
    bool RIGHT = false;
    bool LEFT = false;
    bool UP = false;
    bool DOWN = false;
    while (!quit) {

        SDL_Time currentFrame;
        SDL_GetCurrentTime(&currentFrame);

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

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
            }
        }

        if (W) {
            camera.move(camera.getFront() * cameraSpeed);
        }
        if (S) {
            camera.move(-camera.getFront() * cameraSpeed);
        }
        if (A) {
            camera.move(-camera.getRight() * cameraSpeed);
        }
        if (D) {
            camera.move(camera.getRight() * cameraSpeed);
        }
        if (SPACE) {
            camera.move(glm::vec3(0.0f, 0.05f, 0.0f));
        }
        if (LCTRL) {
            camera.move(glm::vec3(0.0f, -0.05f, 0.0f));
        }
        if (RIGHT) {
            camera.rotate(0.0f, 1.0f);
        }
        if (LEFT) {
            camera.rotate(0.0f, -1.0f);
        }
        if (UP) {
            camera.rotate(-1.0f, 0.0f);
        }
        if (DOWN) {
            camera.rotate(1.0f, 0.0f);
        }

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < objects.size(); i++) {
            Object& current = objects[i];

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(current.getModelMatrix()));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    // Delete all textures when done with them please!!!!!!!!!!!!
    for (int i = 0; i < objects.size(); i++) {
        Object& current = objects[i];
        current.getTexture()->deleteTexture();
    }

    program.deleteProgram();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
