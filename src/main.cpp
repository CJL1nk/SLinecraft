//
// Created by CJ on 3/2/26.
//

#include "includes.h"

int main() {

    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 800;
    constexpr int FOV = 130;

    bool quit = false;

    const float FOCAL_LENGTH = 1.f / std::tan(FOV / 2.f);
    const float SCALE = SCREEN_WIDTH * 0.5f * FOCAL_LENGTH;

    Vec3 cameraPos = {1, 1, -1};

    constexpr float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f
    };

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }

    std::cout << "here" << std::endl;

    SDL_Window* window = SDL_CreateWindow("SLinecraft", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);;
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::cout << "vbo" << std::endl;

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    std::cout << "VAA" << std::endl;

    SDL_GL_SetSwapInterval(1);

    while (!quit) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            switch (event.type) {
                case (SDL_EVENT_KEY_DOWN): {
                    if (event.key.key == SDLK_W) {
                        cameraPos.z -= 0.1f;
                        break;
                    }
                    if (event.key.key == SDLK_S) {
                        cameraPos.z += 0.1f;
                        break;
                    }
                    if (event.key.key == SDLK_D) {
                        cameraPos.x += 0.1f;
                        break;
                    }
                    if (event.key.key == SDLK_A) {
                        cameraPos.x -= 0.1f;
                        break;
                    }
                    if (event.key.key == SDLK_SPACE) {
                        cameraPos.y -= 0.1f;
                        break;
                    }
                    if (event.key.key == SDLK_LCTRL) {
                        cameraPos.y += 0.1f;
                        break;
                    }
                    if (event.key.key == SDLK_Q) {
                        quit = true;
                        break;
                    }
                }
            }
        }

        glViewport(0, 0, 800, 800);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < 12; i += 3) {

            /*Vec3 point1 = {vertices[i + 0], vertices[i + 1], vertices[i + 2]};
            point1.x -= cameraPos.x;
            point1.y -= cameraPos.y;
            point1.z -= cameraPos.z;

            Vec3 point2 = {vertices[i + 0], vertices[i + 1], vertices[i + 2]};
            point2.x -= cameraPos.x;
            point2.y -= cameraPos.y;
            point2.z -= cameraPos.z;

            if (point1.z <= 0 || point2.z <= 0) { continue; }

            float vertices2[] = {
                (point1.x  / point1.z) * SCALE + SCREEN_WIDTH / 2.f, (point1.y / point1.z) * SCALE + SCREEN_HEIGHT / 2.f,
                (point2.x  / point2.z) * SCALE + SCREEN_WIDTH / 2.f, (point2.y / point2.z) * SCALE + SCREEN_HEIGHT / 2.f
            };*/

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        SDL_GL_SwapWindow(window);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
