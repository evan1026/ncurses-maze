#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "MazeCells.h"
#include "MazeRenderer.h"

class MazeGenerator {
    public:
        virtual ~MazeGenerator() {}
        virtual void generate(MazeCells& m, MazeRenderer* r, bool animate, int animationDelay) = 0;
};

#endif
