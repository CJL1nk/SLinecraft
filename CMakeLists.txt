cmake_minimum_required(VERSION 4.1)
project(SLinecraft C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Please install this before trying to compile please please please please please please pleas please please please
# and set up ur paths
find_package(SDL3 REQUIRED)

include_directories(.)

add_executable(SLinecraft

        src/engine/render/glad/src/glad.c

        src/engine/render/shaders/shaders.cpp

        src/engine/render/stb/stb_image.h

        src/engine/render/Texture.cpp
        src/engine/render/Shader.cpp
        src/engine/render/window.cpp

        src/utils/utils.cpp

        src/main.cpp
)

target_link_libraries(SLinecraft PRIVATE SDL3::SDL3)