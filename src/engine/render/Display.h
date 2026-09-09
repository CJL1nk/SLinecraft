//
// Created by CJ on 9/6/26.
//

#ifndef SLINECRAFT_DISPLAY_H
#define SLINECRAFT_DISPLAY_H

#include <SDL3/SDL.h>


class Display {

public:
    /**
     * Initializes a window with OpenGL context
     * @param width Window width
     * @param height Window height
     * @param target_framerate Framerate
     */
    Display(int width, int height, int target_framerate);
    ~Display();

    /**
     * Draws to the window
     */
    void render() const;

    /**
     * Centers your mouse within the window
     */
    void centerMouse() const;

    /**
     * Returns window width
     * @return Window width
     */
    [[nodiscard]] float getWidth() const { return this->width; };
    /**
     * Returns window height
     * @return Window height
     */
    [[nodiscard]] float getHeight() const { return this->height; };
    /**
     * Returns window framerate
     * @return Window framerate
     */
    [[nodiscard]] int getTargetFramerate() const { return this->targetFramerate; };

private:
    float width;
    float height;
    int targetFramerate = 60;
    SDL_Window* window;

    /**
     * Initializes an SDL Window that uses OpenGL.
     * @param width Width of window
     * @param height Height on window
     * @return Pointer to window object
     */
    static SDL_Window* createWindow(uint16_t width, uint16_t height);
};


#endif //SLINECRAFT_DISPLAY_H