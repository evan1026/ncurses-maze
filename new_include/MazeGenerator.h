#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "Maze.h"

class MazeGenerator {
    public:
        virtual ~MazeGenerator() {}
        virtual void generate(Maze& m) = 0;
};

#endif
