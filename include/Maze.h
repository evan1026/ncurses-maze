#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "MazeCell.h"
#include "MazeGeneratorType.h"
#include "Point.h"

class Maze {
    void initGrid();

    MazeCell& getRef(int x, int y);
    MazeCell& getRef(Point p);

    //p is a displacement, not an absolute position
    bool move(Point p);

public:
    const int width;
    const int height;

    const Point start;
    const Point end;

    Maze(int width, int height);
    Maze(int width, int height, MazeGeneratorType g);
    void generate(MazeGeneratorType g);
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

    bool isUnconnected(Point p);
    bool isUnconnected(int x, int y);

    Point getCurrentPosition();

    void setType(int x, int y, MazeCell::Type t);
    void setType(Point p, MazeCell::Type t);
    void setProperties(int x, int y, MazeCell::Properties pr);
    void setProperties(Point p, MazeCell::Properties pr);

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

private:
    std::vector< std::vector< MazeCell > > cells; //It's much easier to initialize if this is declared after width and height
    Point currentPosition;
};

#endif
