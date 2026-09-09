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
        Engine();
        ~Engine();

        void update();
        void render() const;

        void processInputs(float deltaSeconds);

    private:
        void initShaders();

        Display* display;
        Camera* gameCamera;

        std::vector<PointLightSource> pointLights;
        SkyLight skylight;
        World* world;

        ShaderProgram* currProgram;

        signed long int lastFrame = 0;
};


#endif //SLINECRAFT_ENGINE_H