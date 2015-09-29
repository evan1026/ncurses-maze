#ifndef MAZE_H
#define MAZE_H

#include <string>
#include "MazeCells.h"

class Maze{
    int width, height;

    void generate();

public:
    Maze(int w, int h) : width(w), height(h) {
        generate();
    }

    std::string render();
};

#endif
