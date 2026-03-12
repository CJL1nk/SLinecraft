//
// Created by CJ on 3/5/26.
//

#include "shaders.h"

#include <iostream>
#include <cstdarg>

#include "../glad/include/glad/glad.h"

// SHADER DEFINITIONS =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
const char* vertexShaderSource = R"(

    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
        TexCoord = aTexCoord;
    }
)";

const char* fragmentShaderSource = R"(

    #version 330 core
    out vec4 FragColor;

    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D texture1;
    uniform sampler2D texture2;

    void main()
    {
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord) * vec4(ourColor, 1.0), 0.3);
    }
)";
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=


unsigned int createShaderProgram(const int count, ...) {

    const unsigned int shaderProgram = glCreateProgram();

    // Loop through args and attach shaders
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        const unsigned int shader = va_arg(ap, unsigned int );
        glAttachShader(shaderProgram, shader);
    }
    va_end(ap);

    glLinkProgram(shaderProgram);

    // Test if successful
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::LINK::PROGRAM::FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

