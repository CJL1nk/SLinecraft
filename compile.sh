# If someone wants to make a windows version of this that'd be cool

g++ src/main.cpp src/engine/render/glad/src/glad.c src/engine/render/shaders/shaders.cpp src/engine/render/window.cpp -l SDL3 -o SLinecraft
mv ./SLinecraft ./out/