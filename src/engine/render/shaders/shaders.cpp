//
// Created by CJ on 3/5/26.
//
// This file contains only shader programs, will probably also support native GLSL files in the future
//

#include "shaders.h"

// SHADER DEFINITIONS =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
const char* vertexShaderSource = R"(

    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;
    layout (location = 2) in vec3 aNormal;

    out vec2 TexCoord;
    out vec3 Normal;
    out vec3 FragPos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
        Normal = normalize(vec3(1,1,1));
        FragPos = vec3(model * vec4(aPos, 1.0));
    }
)";

const char* fragmentShaderSource = R"(

    #version 330 core
    out vec4 FragColor;

    in vec2 TexCoord;
    in vec3 Normal;
    in vec3 FragPos;

    uniform sampler2D texture1;
    uniform vec3 lightPos;

    float ambientStrength = 0.15;

    void main()
    {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);

        float diff = max(dot(norm, lightDir), 0.0);

        float distance = length(lightPos - FragPos);
        float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

        float lighting = diff * attenuation + ambientStrength;

        FragColor = texture(texture1, TexCoord) * lighting;
    }
)";
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

