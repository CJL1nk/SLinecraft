//
// Created by CJ on 3/20/26.
//

#ifndef SLINECRAFT_SHADERPROGRAM_H
#define SLINECRAFT_SHADERPROGRAM_H

#include <vector>
#include "./glad/include/glad/glad.h"
#include "./Shader.h"

class ShaderProgram {

    public:
        /**
         * Default constructor, initializes a program with a handle
         */
        explicit ShaderProgram(): shaders{}, handle{glCreateProgram()} {};
        ~ShaderProgram();

        /**
         * Adds a shader object into a program
         * @param shader Shader to add
         */
        void add(const Shader* shader);
        /**
         * Adds a shader into the program by handle
         * @param shaderHandle Shader handle to add
         */
        void add(GLuint shaderHandle);

        /**
         * Links a shader program together for usage.
         * @note Must be called after all shaders are added, with .use() being called after to use
         */
        void link() const;

        /**
         * Binds the current program for use
         */
        void use() const;

        /**
         * Deletes the shader program from memory
         */
        void deleteProgram() const;

        /**
         * Returns current program's handle
         * @return Handle of current program
         */
        [[nodiscard]] GLuint getHandle() const;


    private:
        std::vector<GLuint> shaders;
        GLuint handle{};
};


#endif //SLINECRAFT_SHADERPROGRAM_H