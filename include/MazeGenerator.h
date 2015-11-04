#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <ncurses.h>

#include "MazeCells.h"
#include "MazeRenderer.h"

class MazeGenerator {
    public:
        virtual ~MazeGenerator() {}
        virtual void generate(MazeCells& m, WINDOW* win, const MazeRenderer* r, bool animate, int animationDelay) = 0;
};

#endif
