//
// Created by CJ on 3/20/26.
//

#ifndef SLINECRAFT_SHADERPROGRAM_H
#define SLINECRAFT_SHADERPROGRAM_H

#include <vector>
#include "./glad/include/glad/glad.h"
#include "./glm/gtc/type_ptr.hpp"
#include "./Shader.h"
#include "./glm/vec3.hpp"


/**
 * Class holding an OpenGL shader program and its info
 * @note Shader program is NOT deleted on function scope exit, please call .deleteProgram() when it is done being used
 */
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
        void add(const Shader& shader);
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
         * Sets a uniform integer within a shader, given its name.
         * IMPORTANT: CALL AFTER USE()
         * @param name Input integer name
         * @param value Value to assign integer
         * @return Handle of shader uniform
         */
        GLint setInt(const GLchar* name, int value) const;
        /**
         * Sets a uniform float within a shader, given its name.
         * IMPORTANT: CALL AFTER USE()
         * @param name Input float name
         * @param value Value to assign float
         * @return Handle of shader uniform
         */
        GLint setFloat(const GLchar* name, float value) const;
        /**
         * Sets a uniform vec3 within a shader, given its name.
         * IMPORTANT: CALL AFTER USE()
         * @param name Input vector name
         * @param value Value to assign vector
         * @return Handle of shader uniform
         */
        GLint setVec3(const GLchar* name, const glm::vec3& value) const;
        /**
             * Sets a uniform mat4 within a shader, given its name.
             * IMPORTANT: CALL AFTER USE()
             * @param name Input vector name
             * @param value Value to assign vector
             * @return Handle of shader uniform
             */
        GLint setMat4(const GLchar* name, const glm::mat4& value) const;

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