//
// Created by CJ on 9/6/26.
//

#include "Display.h"

#include <iostream>

#include "./glad/include/glad/glad.h"

Display::Display(const int width, const int height, int target_framerate) {

    this->width = width;
    this->height = height;
    this->window = createWindow(width, height);
    SDL_GL_SetSwapInterval(0);
}

Display::~Display() {
    SDL_DestroyWindow(this->window);
}

void Display::render() const {
    glClearColor(0.5f, 1.f, 1.f, 1.0f);
    SDL_GL_SwapWindow(this->window);
}

void Display::centerMouse() const {
    SDL_WarpMouseInWindow(this->window, this->width / 2, this->height / 2);
}


SDL_Window* Display::createWindow(const uint16_t width, const uint16_t height) {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return nullptr;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("SLinecraft", width, height, SDL_WINDOW_OPENGL);
    SDL_GLContext ctx = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}