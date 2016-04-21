#ifndef DFS_MAZE_GENERATOR
#define DFS_MAZE_GENERATOR

#include "Maze.h"
#include "MazeGenerator.h"
#include "Point.h"

/**************************************************************************
 * ~~~~~~~~~~~~~~~~~~~~                                                   *
 * ~ DFSMazeGenerator ~                                                   *
 * ~~~~~~~~~~~~~~~~~~~~                                                   *
 *                                                                        *
 * A type of MazeGenerator that uses a randomized depth first search to   *
 * generate the maze. It starts by continually moving forward in a random *
 * direction until it can no longer continue, then it backtacks until it  *
 * gets to a point where it can move forward again. It continues this     *
 * until the whole maze is filled out.                                    *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

class DFSMazeGenerator : public MazeGenerator {
    Point getRandomUnvisitedDirection(Maze& m, Point p);

public:
    void generate(Maze& m);
};

#endif
