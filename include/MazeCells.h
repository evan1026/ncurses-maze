#ifndef MAZECELLS_H
#define MAZECELLS_H

#include <sstream>

#include "IndexOutOfBoundsException.h"
#include "Point.h"

struct MazeCell {
    enum Type {
        OPEN,
        WALL,
        T_NONE
    };
    enum Properties {
        PART_OF_PATH,
        NOT_PART_OF_PATH,
        P_NONE
    };

    MazeCell::Type type;
    MazeCell::Properties properties;

    MazeCell (MazeCell::Type _t, MazeCell::Properties _p) : type(_t), properties(_p) {}
    MazeCell () : type(MazeCell::Type::T_NONE), properties(MazeCell::Properties::P_NONE) {}
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
    MazeCells(const MazeCells& other) = delete; //copying this guy is a mess, and I never actually need to do it
    ~MazeCells();
    MazeCell get(int x, int y);
    MazeCell get(Point p);
    MazeCell::Type getType(int x, int y);
    MazeCell::Type getType(Point p);
    MazeCell::Properties getProperties(int x, int y);
    MazeCell::Properties getProperties(Point p);
    void set(int x, int y, MazeCell c);
    void set(Point p, MazeCell c);
    void setType(int x, int y, MazeCell::Type t);
    void setType(Point p, MazeCell::Type t);
    void setProperties(int x, int y, MazeCell::Properties pr);
    void setProperties(Point p, MazeCell::Properties pr);
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
