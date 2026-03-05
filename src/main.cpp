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

    std::unordered_map<std::string, Vec3> points;
    std::pair<std::string, std::string> edges[12];

    Vec3 cameraPos = {1, 1, -1};

    points.emplace("A", Vec3({0, 0, 0}));
    points.emplace("B", Vec3({0, 0, 1}));
    points.emplace("C", Vec3({0, 1, 0}));
    points.emplace("D", Vec3({0, 1, 1}));
    points.emplace("E", Vec3({1, 0, 0}));
    points.emplace("F", Vec3({1, 0, 1}));
    points.emplace("G", Vec3({1, 1, 0}));
    points.emplace("H", Vec3({1, 1, 1}));

    edges[0] = std::pair<std::string, std::string>("A", "B");
    edges[1] = std::pair<std::string, std::string>("A", "C");
    edges[2] = std::pair<std::string, std::string>("B", "D");
    edges[3] = std::pair<std::string, std::string>("C", "D");

    edges[4] = std::pair<std::string, std::string>("E", "F");
    edges[5] = std::pair<std::string, std::string>("E", "G");
    edges[6] = std::pair<std::string, std::string>("F", "H");
    edges[7] = std::pair<std::string, std::string>("G", "H");

    edges[8] =  std::pair<std::string, std::string>("A", "E");
    edges[9] =  std::pair<std::string, std::string>("C", "G");
    edges[10] = std::pair<std::string, std::string>("B", "F");
    edges[11] = std::pair<std::string, std::string>("D", "H");

    SDL_Window* window = SDL_CreateWindow("SLinecraft", 800, 800, SDL_WINDOW_OPENGL);;
    SDL_GLContext ctx = SDL_GL_CreateContext(window);

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

        for (int i = 0; i < 12; i++) {

            Vec3 point1 = points.at(edges[i].first);
            point1.x -= cameraPos.x;
            point1.y -= cameraPos.y;
            point1.z -= cameraPos.z;

            Vec3 point2 = points.at(edges[i].second);
            point2.x -= cameraPos.x;
            point2.y -= cameraPos.y;
            point2.z -= cameraPos.z;

            if (point1.z <= 0 || point2.z <= 0) { continue; }

            Vec2 point1Screen = {
                (point1.x  / point1.z) * SCALE + SCREEN_WIDTH / 2.f,
                (point1.y / point1.z) * SCALE + SCREEN_HEIGHT / 2.f};

            Vec2 point2Screen = {
                (point2.x  / point2.z) * SCALE + SCREEN_WIDTH / 2.f,
                (point2.y / point2.z) * SCALE + SCREEN_HEIGHT / 2.f};

            SDL_RenderLine(renderer, point1Screen.x, point1Screen.y, point2Screen.x, point2Screen.y);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
