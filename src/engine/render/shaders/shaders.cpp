//
// Created by CJ on 3/5/26.
//
// This file contains only shader programs, will probably also support native GLSL files in the future
//

#include "shaders.h"

#include <fstream>
#include <sstream>

#include "../../../utils/utils.h"
#include "../../../platform/platform.h"

std::string loadShader(const char* shaderPath) {

#ifdef Linux
    std::string path = pathToLinux(shaderPath);
#endif
#ifdef Win64
    std::string path = pathToWindows(shaderPath).c_str();
#endif

    std::ifstream file(path);
    if (!file.is_open()) return "";

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

