#ifndef DFS_MAZE_GENERATOR
#define DFS_MAZE_GENERATOR

#include <ncurses.h>

#include "MazeCells.h"
#include "MazeGenerator.h"
#include "Point.h"

//DFS -> Depth first search
class DFSMazeGenerator : public MazeGenerator {

    Point getRandomUnvisitedDirection(Point p, MazeCells& cells);

    public:
        void generate(MazeCells& m, std::function<void(Point)> renderFunction, bool animate, int animationDelay);
};

#endif
