//
// Created by CJ on 3/2/26.
//

#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>

#include "./Block.h"
#include "./World.h"

#include "./engine/event.h"
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

    constexpr uint16_t SCREEN_WIDTH = 1920;
    constexpr uint16_t SCREEN_HEIGHT = 1080;
    constexpr float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    constexpr float FOV = 60.0f; // Degrees

    SDL_Window* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Slinecraft");

    Camera camera(FOV, ASPECT_RATIO, 0.1f, 10000.0f);
    const float cameraSpeed = 0.1f;
    glm::vec3 lightPos(0.0f, 60.0f, 0.0f);

    SDL_GL_SetSwapInterval(1);

    // Shaders ---------------------------------------------------------------------------------

    Shader vertexShader(loadShader("../shaders/vert.vert"), GL_VERTEX_SHADER);
    Shader fragmentShader(loadShader("../shaders/frag.frag"), GL_FRAGMENT_SHADER);
    vertexShader.compile();
    fragmentShader.compile();

    ShaderProgram program;
    program.add(vertexShader);
    program.add(fragmentShader);
    program.link();
    program.use();
    program.setVec3("lightPos", lightPos); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS

    glUniform1i(glGetUniformLocation(program.getHandle(), "texture1"), 0); // set it manually

    vertexShader.deleteShader();
    fragmentShader.deleteShader();
    // ------------------------------------------------------------------------------------------------------

    Block::initBlockTextures();
    std::vector<Block> blocks = World::generateWorld();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, blocks[0].getVertexCount() * sizeof(float), blocks[0].getVertices(), GL_STATIC_DRAW); // Hack, but it works

    glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    const int modelLoc = glGetUniformLocation(program.getHandle(), "model");
    const int projLoc = glGetUniformLocation(program.getHandle(), "projection");
    const int viewLoc = glGetUniformLocation(program.getHandle(), "view");

    // Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);

    signed long int  lastFrame = 0;
    while (!quit) {

        SDL_Time currentFrame;
        SDL_GetCurrentTime(&currentFrame);

        SDL_Time deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float deltaSeconds = (float)deltaTime / 10000000.0f;

        float cameraVelocity = cameraSpeed * deltaSeconds;

        pollEvents();

        if (W) {
            camera.move(camera.getFront() * cameraVelocity);
        }
        if (S) {
            camera.move(-camera.getFront() * cameraVelocity);
        }
        if (A) {
            camera.move(-camera.getRight() * cameraVelocity);
        }
        if (D) {
            camera.move(camera.getRight() * cameraVelocity);
        }
        if (P) {
            std::cout << "x: " << camera.getPosition().x << " y: " << camera.getPosition().y << " z: " << camera.getPosition().z << std::endl;
        }
        if (SPACE) {
            camera.move(camera.getUp() * cameraVelocity);
        }
        if (LCTRL) {
            camera.move(-camera.getUp() * cameraVelocity);
        }
        if (RIGHT) {
            camera.rotate(0.0f, 1.0f * deltaSeconds);
        }
        if (LEFT) {
            camera.rotate(0.0f, -1.0f * deltaSeconds);
        }
        if (UP) {
            camera.rotate(-1.0f * deltaSeconds, 0.0f);
        }
        if (DOWN) {
            camera.rotate(1.0f * deltaSeconds, 0.0f);
        }

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < blocks.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, blocks[i].getTexture()->getHandle());
            Object& current = blocks[i];

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(current.getModelMatrix()));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    // Delete all textures when done with them please!!!!!!!!!!!!
    for (int i = 0; i < blocks.size(); i++) {
        Object& current = blocks[i];
        current.getTexture()->deleteTexture();
    }

    program.deleteProgram();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
