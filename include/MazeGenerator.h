#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "Maze.h"

class MazeGenerator {
protected:
    MazeGenerator() = default;
public:
    virtual ~MazeGenerator() {}
    MazeGenerator(const MazeGenerator& m) = default;
    MazeGenerator(MazeGenerator&& m) = default;
    MazeGenerator& operator=(const MazeGenerator& m) = default;
    MazeGenerator& operator=(MazeGenerator&& m) = default;

    virtual void generate(Maze& m) = 0;
};

#endif
