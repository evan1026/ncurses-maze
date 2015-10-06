#ifndef MAZE_H
#define MAZE_H

#include <string>
#include "MazeCells.h"
#include "Point.h"

class Maze{
    int width, height;
    MazeCells cells;

    void generate();
    Point getRandomUnvisitedDirection(Point p);

public:
    Maze(int w, int h) : width(w), height(h), cells(2 * w + 1, 2 * h + 1) {
        generate();
    }

    std::string render();
};

#endif
