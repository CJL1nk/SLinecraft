//
// Created by CJ on 3/5/26.
//

#ifndef SLINECRAFT_TEMP_H
#define SLINECRAFT_TEMP_H
#include <string>

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

/**
 * Returns a shaders source string
 * @param shaderPath Path to shader
 * @return Source string of shader
 */
std::string loadShader(const char* shaderPath);

#endif //SLINECRAFT_TEMP_H