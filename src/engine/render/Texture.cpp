//
// Created by CJ on 3/9/26.
//

#define STB_IMAGE_IMPLEMENTATION

#include "./Texture.h"
#include "./stb/stb_image.h"
#include "../../platform/platform.h"
#include "../../utils/utils.h"

void Texture::load() {

    unsigned int textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load image data into buffer
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);  // So image isn't upside down
#ifdef Linux
    unsigned char* data = stbi_load(pathToLinux(this->filename).c_str(), &width, &height, &nrChannels, 0);
#endif
#ifdef Win64
    unsigned char* data = stbi_load(pathToWindows(this->filename).c_str(), &width, &height, &nrChannels, 0);
#endif

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, this->format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
    this->handle = textureHandle;
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->handle);
}

void Texture::deleteTexture() const {
    glDeleteTextures(1, &this->handle);
}

GLuint Texture::getHandle() const {
    return this->handle;
}