//
// Created by CJ on 3/5/26.
//

#include "shaders.h"

#include <iostream>
#include <stdarg.h>

#include "../glad/include/glad/glad.h"

// SHADER DEFINITIONS =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
const char* vertexShaderSource = R"(

    #version 330 core
    layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
    layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

    out vec3 ourColor; // output a color to the fragment shader

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor; // set ourColor to the input color we got from the vertex data
    }
)";

const char* fragmentShaderSource = R"(

    #version 330 core
    out vec4 FragColor;
    in vec3 ourColor;

    void main()
    {
        FragColor = vec4(ourColor, 1.0);
    }
)";
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

unsigned int compileShader(const uint32_t shaderType, const char* source) {

    // Compile shader
    const unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Test if successful
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int createShaderProgram(const int count, ...) {

    const unsigned int shaderProgram = glCreateProgram();

    // Loop through args and attach shaders
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i <= count; i++) {
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

