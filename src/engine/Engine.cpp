//
// Created by CJ on 9/6/26.
//

#include "Engine.h"

#include <iostream>

#include "event.h"
#include "render/Shader.h"
#include "render/ShaderProgram.h"
#include "render/shaders/shaders.h"
#include "../World.h"

Engine::Engine() {
    this->display = new Display(1920, 1080, 60);
    this->gameCamera = new Camera(70.0f, this->display->getWidth() / this->display->getHeight(), 0.1f, 1000.0f);

    Block::initBlockTextures();
    this->blocks = World::generateWorld();
    initShaders();
}

Engine::~Engine() {
    delete this->display;
    delete this->gameCamera;
}

void Engine::update() {

    // PROBABLY DON'T NEED TO DO THIS EVERY FRAME
    const int modelLoc = glGetUniformLocation(this->currProgram->getHandle(), "model");
    const int projLoc = glGetUniformLocation(this->currProgram->getHandle(), "projection");
    const int viewLoc = glGetUniformLocation(this->currProgram->getHandle(), "view");

    SDL_Time currentFrame;
    SDL_GetCurrentTime(&currentFrame);

    SDL_Time deltaTime = currentFrame - this->lastFrame;
    this->lastFrame = currentFrame;

    float deltaSeconds = (float)deltaTime / 10000000.0f;

    pollEvents();
    processInputs(deltaSeconds);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(this->gameCamera->getProjection()));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->gameCamera->getView()));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < blocks.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, blocks[i].getTexture()->getHandle());
        Object& current = blocks[i];

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(current.getModelMatrix()));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    display->render();
}

void Engine::processInputs(float deltaSeconds) {

    float cameraVelocity = this->gameCamera->getSpeed() * deltaSeconds;

    if (W) {
        this->gameCamera->move(this->gameCamera->getFlatFront() * cameraVelocity);
        randomKid.position += this->gameCamera->getFlatFront() * cameraVelocity;
        currProgram->setVec3("light.position", randomKid.position);
    }
    if (S) {
        this->gameCamera->move(-this->gameCamera->getFlatFront() * cameraVelocity);
        randomKid.position += -this->gameCamera->getFlatFront()  * cameraVelocity;
        currProgram->setVec3("light.position", randomKid.position);
    }
    if (A) {
        this->gameCamera->move(-this->gameCamera->getRight() * cameraVelocity);
        randomKid.position += -this->gameCamera->getRight() * cameraVelocity;
        currProgram->setVec3("light.position", randomKid.position);
    }
    if (D) {
        this->gameCamera->move(this->gameCamera->getRight() * cameraVelocity);
        randomKid.position += this->gameCamera->getRight() * cameraVelocity;
        currProgram->setVec3("light.position", randomKid.position);
    }
    if (P) {
        std::cout << "x: " << this->gameCamera->getPosition().x << " y: " << this->gameCamera->getPosition().y << " z: " << this->gameCamera->getPosition().z << std::endl;
        blocks.push_back(Block(glm::vec3(this->gameCamera->getPosition().x, this->gameCamera->getPosition().y - 1.0f, this->gameCamera->getPosition().z), 1));
    }
    if (SPACE) {
        this->gameCamera->move(this->gameCamera->getUp() * cameraVelocity);
        randomKid.position += this->gameCamera->getUp() * cameraVelocity;
        currProgram->setVec3("light.position", randomKid.position);
    }
    if (LCTRL) {
        this->gameCamera->move(-this->gameCamera->getUp() * cameraVelocity);
        randomKid.position += -this->gameCamera->getUp() * cameraVelocity;
        currProgram->setVec3("light.position", randomKid.position);
    }
    if (RIGHT) {
        this->gameCamera->rotate(0.0f, 1.5f * deltaSeconds);
    }
    if (LEFT) {
        this->gameCamera->rotate(0.0f, -1.5f * deltaSeconds);
    }
    if (UP) {
        this->gameCamera->rotate(-1.5f * deltaSeconds, 0.0f);
    }
    if (DOWN) {
        this->gameCamera->rotate(1.5f * deltaSeconds, 0.0f);
    }
}


// This currently does more than just init shaders
void Engine::initShaders() {

    Shader vertexShader(loadShader("../shaders/vert.vert"), GL_VERTEX_SHADER);
    Shader fragmentShader(loadShader("../shaders/frag.frag"), GL_FRAGMENT_SHADER);
    vertexShader.compile();
    fragmentShader.compile();

    this->currProgram = new ShaderProgram();
    this->currProgram->add(vertexShader);
    this->currProgram->add(fragmentShader);
    this->currProgram->link();
    this->currProgram->use();

    randomKid = {glm::vec3(0.f, 0.0f, 0.0f), glm::vec3(1.f, 1.f, 1.0f)};

    // CALL AFTER USE()!!!! AFTER!!!!! I SPENT LIKE FOREVER DEBUGGING THIS
    this->currProgram->setVec3("light.position", randomKid.position);
    this->currProgram->setMat4("view", gameCamera->getView());
    this->currProgram->setFloat("light.strength", randomKid.strength);
    this->currProgram->setVec3("light.diffuse", randomKid.diffuse);
    this->currProgram->setFloat("light.constant", randomKid.constant);
    this->currProgram->setFloat("light.linear", randomKid.linear);
    this->currProgram->setFloat("light.quadratic", randomKid.quadratic);
    this->currProgram->setFloat("ambient", 0.05f);
    this->currProgram->setFloat("skylight", 0.0f);

    glUniform1i(glGetUniformLocation(this->currProgram->getHandle(), "texture1"), 0); // set it manually

    vertexShader.deleteShader();
    fragmentShader.deleteShader();



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

    // Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
}
