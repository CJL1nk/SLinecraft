cmake_minimum_required(VERSION 4.1)
project(SLinecraft CXX)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SLinecraft
        src/platform/Win64.h
        src/platform/Linux.h
        src/main.cpp
    )
