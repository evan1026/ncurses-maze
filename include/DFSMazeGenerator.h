#ifndef DFS_MAZE_GENERATOR
#define DFS_MAZE_GENERATOR

#include "Maze.h"
#include "MazeGenerator.h"
#include "Point.h"

//DFS -> Depth first search
class DFSMazeGenerator : public MazeGenerator {

    Point getRandomUnvisitedDirection(Maze& m, Point p);

public:
    void generate(Maze& m);
};

#endif
