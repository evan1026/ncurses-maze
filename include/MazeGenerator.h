#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "Maze.h"

/**********************************************************************
 * ~~~~~~~~~~~~~~~~~                                                  *
 * ~ MazeGenerator ~                                                  *
 * ~~~~~~~~~~~~~~~~~                                                  *
 *                                                                    *
 * An abstract class that serves as the base for all types of maze    *
 * generators. The main function, generate(), takes in the blank maze *
 * and modifies it to be an actual, solvable maze.                    *
 **********************************************************************/

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
