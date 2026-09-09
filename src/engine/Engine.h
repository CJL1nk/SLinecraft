//
// Created by CJ on 9/6/26.
//

#ifndef SLINECRAFT_ENGINE_H
#define SLINECRAFT_ENGINE_H

#include "render/Camera.h"
#include "render/Display.h"
#include "../Block.h"
#include "render/ShaderProgram.h"
#include "src/World.h"

struct PointLightSource {
    glm::vec3 position;
    glm::vec3 diffuse = {1.f, 1.f, 1.f};

    float strength = 3.0f;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};

struct SkyLight {
    glm::vec3 direction;
    glm::vec3 strength;
};

class Engine {

    public:
        /**
         * Initializes the game engine and loads relevant pieces
         */
        Engine();
        ~Engine();

        /**
         * Ticks and updates the interneal engine state
         */
        void update();
        /**
         * Renders the game to the screen
         */
        void render() const;

        /**
         * Processes the inputs updated by pollEvents() and updates the engine state
         * @param deltaSeconds Seconds since the last engine update
         */
        void processInputs(float deltaSeconds);

    private:
        Display* display;
        Camera* gameCamera;

        std::vector<PointLightSource> pointLights;
        SkyLight skylight;
        World* world;

        ShaderProgram* currProgram;

        signed long int lastFrame = 0;

        /**
         * Initializes shaders and does some other stuff it shouldn't do but I don't care right now
         */
        void initShaders();
};


#endif //SLINECRAFT_ENGINE_H