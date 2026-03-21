//
// Created by CJ on 3/9/26.
//

#ifndef SLINECRAFT_TEXTURE_H
#define SLINECRAFT_TEXTURE_H

#include "./glad/include/glad/glad.h"

/**
 * Class holding an OpenGL texture and its info
 * @note Texture is NOT deleted on function scope exit, please call .deleteTexture() when it is done being used
 */
class Texture {
    public:
        /**
         * Initializes (but does not load) a texture object
         * @param filename Path to texture file
         * @param format Color format of texture (GL_RGB, GL_RGBA, ...)
         */
        Texture(const char* filename, const GLuint format) : filename(filename), format(format) {};

        /**
        * Loads a texture into the GPU resources and sets the handle
        */
        void load();

        /**
        * Binds a texture for drawing.
        * This function will very likely just get removed because it is a wrapper over a single OpenGL function
        */
        void bind() const;

        /**
         * Deletes the texture from memory
         */
        void deleteTexture() const;

        /**
         * Returns the handle of current texture object
         * @return Handle of current texture object
         */
        [[nodiscard]] GLuint getHandle() const;

    private:
        const char* filename;
        GLuint format;
        GLuint handle{};
};

#endif //SLINECRAFT_TEXTURE_H