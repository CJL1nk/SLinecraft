//
// Created by CJ on 3/9/26.
//

#define STB_IMAGE_IMPLEMENTATION

#include <filesystem>

#include "./glad/include/glad/glad.h"
#include "./stb/stb_image.h"

unsigned int loadTexture2D(const char* filename) {

    const std::filesystem::path path(filename);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load image data into buffer
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    return texture;
}

void bindTexture2D(const unsigned int handle) {
    glBindTexture(GL_TEXTURE_2D, handle);
}