#ifndef MAZECELLS_H
#define MAZECELLS_H

#include <sstream>

#include "Point.h"
#include "IndexOutOfBoundsException.h"

enum MazeCell {
    OPEN,
    WALL,
    NONE
};

class MazeCells {
    MazeCell** cells;
    int width, height;
    
    static const Point left;
    static const Point right;
    static const Point up;
    static const Point down;

public:
    MazeCells(int w, int h);
    ~MazeCells();
    MazeCell get(int x, int y);
    MazeCell get(Point p);
    void set(int x, int y, MazeCell c);
    void set(Point p, MazeCell c);
    bool isUnconnected(int x, int y);
    bool isUnconnected(Point p);

    int getHeight() {
        return height;
    }
    int getWidth() {
        return width;
    }
    
    MazeCell upperNeighbor(Point p) {
        return get(p + up);
    }
    MazeCell lowerNeighbor(Point p) {
        return get(p + down);
    }
    MazeCell rightNeighbor(Point p) {
        return get(p + right);
    }
    MazeCell leftNeighbor(Point p) {
        return get(p + left);
    }

    MazeCell upperNeighbor(int x, int y) {
        return upperNeighbor(Point(x,y));
    }
    MazeCell lowerNeighbor(int x, int y) {
        return lowerNeighbor(Point(x,y));
    }
    MazeCell leftNeighbor(int x, int y) {
        return leftNeighbor(Point(x,y));
    }
    MazeCell rightNeighbor(int x, int y) {
        return rightNeighbor(Point(x,y));
    }
};

#endif
