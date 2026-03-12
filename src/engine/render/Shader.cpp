//
// Created by CJ on 3/12/26.
//

#include <iostream>
#include <cstdarg>

#include "Shader.h"

Shader::~Shader() {
    glDeleteShader(this->handle);
}

void Shader::compile() {

    const GLuint shader = glCreateShader(this->type);
    glShaderSource(shader, 1, &this->source, nullptr);
    glCompileShader(shader);

    // Test if successful
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->handle = shader;
}

void Shader::deleteShader() {
    glDeleteShader(this->handle);
}

GLuint Shader::getHandle() const {
    return this->handle;
}

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