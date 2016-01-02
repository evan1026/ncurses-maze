#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "MazeCell.h"
#include "Point.h"

class Maze {
    
    void initGrid();

public:
    const int width;
    const int height;
    
    Maze(int width, int height);
    void generate();
    MazeCell get(int x, int y);
    MazeCell get(Point p);
    
    MazeCell getUpperNeighbor(int x, int y);
    MazeCell getUpperNeighbor(Point p);
    MazeCell getLowerNeighbor(int x, int y);
    MazeCell getLowerNeighbor(Point p);
    MazeCell getRightNeighbor(int x, int y);
    MazeCell getRightNeighbor(Point p);
    MazeCell getLeftNeighbor(int x, int y);
    MazeCell getLeftNeighbor(Point p);
    
private:
    std::vector< std::vector< MazeCell > > cells; //It's much easier to initialize if this is declared after width and height
};

#endif
