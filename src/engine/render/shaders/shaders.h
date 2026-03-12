//
// Created by CJ on 3/5/26.
//

#ifndef SLINECRAFT_TEMP_H
#define SLINECRAFT_TEMP_H

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

/**
 * Creates and links a GL shader program given shader handles to attach.
 * Does NOT delete shaders after linking program.
 * @param count Number of shaders to attach
 * @param ... Shaders handles to attach
 * @return Handle of linked shader program
 */
unsigned int createShaderProgram(int count, ...);

#endif //SLINECRAFT_TEMP_H