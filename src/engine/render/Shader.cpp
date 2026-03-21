//
// Created by CJ on 3/12/26.
//

#include <iostream>

#include "Shader.h"

Shader::~Shader() {
    //glDeleteShader(this->handle);
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