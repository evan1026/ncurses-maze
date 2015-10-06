#ifndef MAZE_H
#define MAZE_H

#include <string>
#include "MazeCells.h"
#include "Point.h"

class Maze{
    int width, height;
    MazeCells cells;

    void generate(bool animate, int animationDelay);
    Point getRandomUnvisitedDirection(Point p);

public:

    Maze (int w, int h, bool animate, int animationDelay) : width(w), height(h),
                                                            cells(2 * w + 1, 2 * h + 1)
    {
        generate(animate, animationDelay);
    }
    Maze (int w, int h, bool animate) : Maze(w,h,animate,50) {}
    Maze (int w, int h) : Maze(w,h,false,0) {}

    void render();
};

#endif
