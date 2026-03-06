//
// Created by CJ on 3/5/26.
//

#ifndef SLINECRAFT_TEMP_H
#define SLINECRAFT_TEMP_H

#include <cstdint>

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

/**
 * Compiles a GLSL shader given a type and source string
 * @param shaderType Type of shader to compile (Macros defined in glad.h)
 * @param source String containing source GLSL
 * @return Handle of compiled shader
 */
unsigned int compileShader(uint32_t shaderType, const char* source);

#endif //SLINECRAFT_TEMP_H