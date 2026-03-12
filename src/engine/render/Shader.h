//
// Created by CJ on 3/12/26.
//

#ifndef SLINECRAFT_SHADER_H
#define SLINECRAFT_SHADER_H

#include "glad/include/glad/glad.h"

class Shader {
    public:
        /**
         * Initializes (but does not compile) a shader object
         * @param source String containing shader source
         * @param type Type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, ...)
         */
        Shader(const char* source, const GLuint type) : source(source), type(type) {};
        // Will also support shader file here later
        ~Shader();

        /**
        * Compiles the current GLSL shader from its source and sets the handle
        */
        void compile();
        /**
         * Deletes a shader from GPU memory (safe to call after shader has been compiled)
         */
        void deleteShader();
        /**
         * Returns the handle of current shader object
         * @return Handle of current shader object
         */
        [[nodiscard]] GLuint getHandle() const;

    private:
        const char* source;
        GLuint type;
        GLuint handle{};
};

/**
 * Creates and links a GL shader program given shader handles to attach.
 * Does NOT delete shaders after linking program.
 * @param count Number of shaders to attach
 * @param ... Shaders handles to attach
 * @return Handle of linked shader program
 */
unsigned int createShaderProgram(int count, ...);


#endif //SLINECRAFT_SHADER_H