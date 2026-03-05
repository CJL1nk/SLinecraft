# If someone wants to make a windows version of this that'd be cool

g++ src/platform/Win64.h src/platform/Linux.h src/engine/types.h src/engine/Block.h src/engine/Block.cpp src/includes.h src/main.cpp -o SLinecraft
mv ./SLinecraft ./out/