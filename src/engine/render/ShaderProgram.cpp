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

GLint ShaderProgram::setInt(const GLchar* name, const int value) const {
    const GLint uniformHandle = glGetUniformLocation(this->handle, name);
    glUniform1i(uniformHandle, value);
    return uniformHandle;
}

GLint ShaderProgram::setFloat(const GLchar* name, const float value) const {
    const GLint uniformHandle = glGetUniformLocation(this->handle, name);
    glUniform1f(uniformHandle, value);
    return uniformHandle;
}

GLint ShaderProgram::setVec3(const GLchar* name, const glm::vec3& value) const {
    const GLint uniformHandle = glGetUniformLocation(this->handle, name);
    glUniform3fv(uniformHandle, 1, &value[0]);
    return uniformHandle;
}

GLint ShaderProgram::setMat4(const GLchar* name, const glm::mat4& value) const {
    const GLint uniformHandle = glGetUniformLocation(this->handle, name);
    glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(value));
    return uniformHandle;
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