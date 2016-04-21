#ifndef PRIMS_MAZE_GENERATOR
#define PRIMS_MAZE_GENERATOR

#include "Maze.h"
#include "MazeGenerator.h"
#include "Point.h"

/**************************************************************************
 * ~~~~~~~~~~~~~~~~~~~~~~                                                 *
 * ~ PrimsMazeGenerator ~                                                 *
 * ~~~~~~~~~~~~~~~~~~~~~~                                                 *
 *                                                                        *
 * A maze generator that uses a randomized version of Prim's algorithm.   *
 * Information about how it works can be found at https://goo.gl/xWWZAj   *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

class PrimsMazeGenerator : public MazeGenerator {
    static Point directions[];
    Point start;

    bool isInMaze(Point p, Maze& m);
    void removePoint(int index, std::vector<Point>& container);
    bool vecContains(Point p, std::vector<Point>& container);

public:
    void generate(Maze& m);
};

#endif
