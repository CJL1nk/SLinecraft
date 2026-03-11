//
// Created by CJ on 3/9/26.
//

#ifndef SLINECRAFT_TEXTURE_H
#define SLINECRAFT_TEXTURE_H

/**
 * Loads a texture into the GPU resources
 * @param filename Path of texture to load
 * @return Handle (ID) of loaded texture
 */
unsigned int loadTexture2D(const char* filename);

/**
 * Binds a texture for drawing.
 * This function will very likely just get removed because it is a wrapper over a single OpenGL function
 * @param handle Handle of texture to bind
 */
inline void bindTexture2D(unsigned int handle);

#endif //SLINECRAFT_TEXTURE_H