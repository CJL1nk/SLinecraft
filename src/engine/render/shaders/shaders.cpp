//
// Created by CJ on 3/5/26.
//

#include "shaders.h"

#include <iostream>

#include "src/engine/render/glad/include/glad/glad.h"

// SHADER DEFINITIONS =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
const char* vertexShaderSource = R"(

    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

const char* fragmentShaderSource = R"(

    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0,1.0,1.0,1.0);
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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

