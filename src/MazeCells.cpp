#include <sstream>

#include "MazeCells.h"
#include "Point.h"
#include "IndexOutOfBoundsException.h"

const Point MazeCells::left  = Point(-1,  0);
const Point MazeCells::right = Point( 1,  0);
const Point MazeCells::up    = Point( 0, -1);
const Point MazeCells::down  = Point( 0,  1);

MazeCells::MazeCells(int w, int h) : width(w), height(h) {
    cells = new MazeCell*[width];
    for (int i = 0; i < width; ++i)
        cells[i] = new MazeCell[height];

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (i % 2 == 1 && j % 2 == 1)
                cells[i][j].type = MazeCell::Type::OPEN;
            else
                cells[i][j].type = MazeCell::Type::WALL;
        }
    }
}
MazeCells::~MazeCells() {
    for (int i = 0; i < width; ++i)
        delete[] cells[i];
    delete[] cells;
}

MazeCell MazeCells::get(int x, int y) {
    if (x < width && x >= 0 && y < height && y >= 0)
        return cells[x][y];

    return MazeCell(MazeCell::Type::T_NONE, MazeCell::Properties::P_NONE);
}
MazeCell MazeCells::get(Point p) {
    return get(p.x, p.y);
}

MazeCell::Type MazeCells::getType(int x, int y) {
    return get(x, y).type;
}
MazeCell::Type MazeCells::getType(Point p) {
    return getType(p.x, p.y);
}

MazeCell::Properties MazeCells::getProperties(int x, int y) {
    return get(x, y).properties;
}
MazeCell::Properties MazeCells::getProperties(Point p) {
    return getProperties(p.x, p.y);
}

void MazeCells::set(int x, int y, MazeCell c) {
    std::stringstream exceptionDetails;
    bool except = false;
    exceptionDetails << "In MazeCells::set(int, int, MazeCell): ";
    if (x >= width) {
        exceptionDetails << "{x >= width x=" << x << " width=" << width << "} ";
        except = true;
    } else if (x < 0) {
        exceptionDetails << "{x < 0 x=" << x << "} ";
        except = true;
    }
    if (y >= height) {
        exceptionDetails << "{y >= height y=" << y << " height=" << height << "} ";
        except = true;
    } else if (y < 0) {
        exceptionDetails << "{y < 0 y=" << y << "} ";
        except = true;
    }

    if (except) 
        throw IndexOutOfBoundsException(exceptionDetails.str());

    cells[x][y] = c;
}
void MazeCells::set(Point p, MazeCell c) {
    set(p.x, p.y, c);
}

void MazeCells::setType(int x, int y, MazeCell::Type t) {
    MazeCell::Properties p = getProperties(x, y);
    set(x, y, MazeCell(t, p));
}
void MazeCells::setType(Point p, MazeCell::Type t) {
    setType(p.x, p.y, t);
}

void MazeCells::setProperties(int x, int y, MazeCell::Properties pr) {
    MazeCell::Type t = getType(x, y);
    set(x, y, MazeCell(t, pr));
}
void MazeCells::setProperties(Point p, MazeCell::Properties pr) {
    setProperties(p.x, p.y, pr);
}

bool MazeCells::isUnconnected(int x, int y) {
    return (get(x - 1, y).type == MazeCell::Type::WALL) &&
           (get(x + 1, y).type == MazeCell::Type::WALL) &&
           (get(x, y - 1).type == MazeCell::Type::WALL) &&
           (get(x, y + 1).type == MazeCell::Type::WALL);
}

bool MazeCells::isUnconnected(Point p) {
    return isUnconnected(p.x, p.y);
}
