//
// Created by CJ on 9/6/26.
//

#ifndef SLINECRAFT_DISPLAY_H
#define SLINECRAFT_DISPLAY_H

#include <SDL3/SDL.h>


class Display {

public:
    Display(int width, int height, int target_framerate);

    void render();

    int getWidth() const { return this->width; };
    int getHeight() const { return this->height; };
    int getTargetFramerate() const { return this->targetFramerate; };

        /**
     * Initializes an SDL Window that uses OpenGL.
     * @param width Width of window
     * @param height Height on window
     * @return Pointer to window object
     */
    static SDL_Window* createWindow(uint16_t width, uint16_t height);

private:
    int width;
    int height;
    int targetFramerate = 60;
    SDL_Window* window;
};


#endif //SLINECRAFT_DISPLAY_H