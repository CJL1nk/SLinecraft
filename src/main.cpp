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

struct PointLightSource {
    glm::vec3 position;
    glm::vec3 diffuse;
    glm::vec3 direction;

    float strength = 2.0f;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};

int main() {

    constexpr uint16_t SCREEN_WIDTH = 1920;
    constexpr uint16_t SCREEN_HEIGHT = 1080;
    constexpr float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    constexpr float FOV = 70.0f; // Degrees

    SDL_Window* window = initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Slinecraft");

    Camera camera(FOV, ASPECT_RATIO, 0.1f, 10000.0f);
    const float cameraSpeed = 0.1f;

    PointLightSource light = {glm::vec3(0.f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3( 0.0f, -1.0f, 0.0f)};

    SDL_GL_SetSwapInterval(0);

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

    program.setVec3("light.position", light.position); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THISprogram.setVec3("light.diffuse", light.diffuse); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    program.setFloat("light.strength", light.strength); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    program.setVec3("light.direction", light.direction); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    program.setFloat("light.constant", light.constant); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    program.setFloat("light.linear", light.linear); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    program.setFloat("light.quadratic", light.quadratic); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    program.setFloat("ambient", 0.05f); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    program.setFloat("skylight", 0.0f); // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS

    program.setMat4("view", camera.getView());

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

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    const int modelLoc = glGetUniformLocation(program.getHandle(), "model");
    const int projLoc = glGetUniformLocation(program.getHandle(), "projection");
    const int viewLoc = glGetUniformLocation(program.getHandle(), "view");

    // Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glClearColor(0.f, 0.03f, 0.05f, 1.0f);

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
            camera.move(camera.getFlatFront() * cameraVelocity);
            light.position += camera.getFlatFront() * cameraVelocity;
            program.setVec3("light.position", light.position);
        }
        if (S) {
            camera.move(-camera.getFlatFront() * cameraVelocity);
            light.position += -camera.getFlatFront()  * cameraVelocity;
            program.setVec3("light.position", light.position);
        }
        if (A) {
            camera.move(-camera.getRight() * cameraVelocity);
            light.position += -camera.getRight() * cameraVelocity;
            program.setVec3("light.position", light.position);
        }
        if (D) {
            camera.move(camera.getRight() * cameraVelocity);
            light.position += camera.getRight() * cameraVelocity;
            program.setVec3("light.position", light.position);
        }
        if (P) {
            std::cout << "x: " << camera.getPosition().x << " y: " << camera.getPosition().y << " z: " << camera.getPosition().z << std::endl;
            blocks.push_back(Block(glm::vec3(camera.getPosition().x, camera.getPosition().y - 1.0f, camera.getPosition().z), 1));
        }
        if (SPACE) {
            camera.move(camera.getUp() * cameraVelocity);
            light.position += camera.getUp() * cameraVelocity;
            program.setVec3("light.position", light.position);
        }
        if (LCTRL) {
            camera.move(-camera.getUp() * cameraVelocity);
            light.position += -camera.getUp() * cameraVelocity;
            program.setVec3("light.position", light.position);
        }
        if (RIGHT) {
            camera.rotate(0.0f, 1.5f * deltaSeconds);
        }
        if (LEFT) {
            camera.rotate(0.0f, -1.5f * deltaSeconds);
        }
        if (UP) {
            camera.rotate(-1.5f * deltaSeconds, 0.0f);
        }
        if (DOWN) {
            camera.rotate(1.5f * deltaSeconds, 0.0f);
        }

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));

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
