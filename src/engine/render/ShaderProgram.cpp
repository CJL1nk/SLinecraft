//
// Created by CJ on 3/20/26.
//

#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::~ShaderProgram() = default;/*{
    //glDeleteProgram(this->handle);
}*/

void ShaderProgram::add(const Shader& shader) {
    this->shaders.push_back(shader.getHandle());
    glAttachShader(this->handle, shader.getHandle());
}

void ShaderProgram::add(const GLuint shaderHandle) {
    this->shaders.push_back(shaderHandle);
    glAttachShader(this->handle, shaderHandle);
}

void ShaderProgram::link() const {

    glLinkProgram(this->handle);

    int success;
    char infoLog[512];
    glGetProgramiv(this->handle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->handle, 512, nullptr, infoLog);
        std::cout << "ERROR::LINK::PROGRAM::FAILED\n" << infoLog << std::endl;
    }
}

GLint ShaderProgram::setVec3(const GLchar* name, const glm::vec3& value) {
    const GLint handle = glGetUniformLocation(this->handle, name);
    glUniform3fv(handle, 1, &value[0]);
    return handle;
}

void ShaderProgram::use() const {
    glUseProgram(this->handle);
}

void ShaderProgram::deleteProgram() const {
    glDeleteProgram(this->handle);
}

GLuint ShaderProgram::getHandle() const {
    return this->handle;
}