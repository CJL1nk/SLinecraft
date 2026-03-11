//
// Created by CJ on 3/11/26.
//

#include <algorithm>
#include "utils.h"


std::string pathToLinux(const char* path) {
    std::string newPath = path;
    std::replace(newPath.begin(), newPath.end(), '\\', '/');

    return newPath.c_str();
}

std::string pathToWindows(const char* path) {
    std::string newPath = path;
    std::replace(newPath.begin(), newPath.end(), '/', '\\');

    return newPath.c_str();
}
