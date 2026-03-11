//
// Created by CJ on 3/11/26.
//

#ifndef SLINECRAFT_UTILS_H
#define SLINECRAFT_UTILS_H

#include <string>

/**
 * Converts some given path to a Linux path (i.e. replaces all '\' with '/').
 * @note If some given function is asking for a const char*, .c_str() can be used on the return value of this function to make compatible
 * @param path Path to convert
 * @return Converted Linux path
 */
std::string pathToLinux(const char* path);

/**
 * Converts some given path to a Windows path (i.e. replaces all '/' with '\').
 * @note If some given function is asking for a const char*, .c_str() can be used on the return value of this function to make compatible
 * @param path Path to convert
 * @return Converted Windows path
 */
std::string pathToWindows(const char* path);

#endif //SLINECRAFT_UTILS_H