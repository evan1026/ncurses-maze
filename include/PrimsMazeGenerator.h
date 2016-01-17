#ifndef PRIMS_MAZE_GENERATOR
#define PRIMS_MAZE_GENERATOR

#include "Maze.h"
#include "MazeGenerator.h"
#include "Point.h"

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
