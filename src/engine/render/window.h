//
// Created by CJ on 3/5/26.
//

#ifndef SLINECRAFT_WINDOW_H
#define SLINECRAFT_WINDOW_H

#include <SDL3/SDL.h>

/**
 * Initializes an SDL Window that uses OpenGL
 * @param width Width of window
 * @param height Height on window
 * @param title Window title
 * @return Pointer to window object
 */
SDL_Window* initWindow(uint16_t width, uint16_t height, const char* title);

#endif //SLINECRAFT_WINDOW_H