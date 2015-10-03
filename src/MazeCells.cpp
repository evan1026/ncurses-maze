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
                cells[i][j] = MazeCell::OPEN;
            else
                cells[i][j] = MazeCell::WALL;
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

    return MazeCell::NONE;
}

MazeCell MazeCells::get(Point p) {
    return get(p.x, p.y);
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

bool MazeCells::isUnconnected(int x, int y) {
    return (get(x - 1, y) == MazeCell::WALL) &&
           (get(x + 1, y) == MazeCell::WALL) &&
           (get(x, y - 1) == MazeCell::WALL) &&
           (get(x, y + 1) == MazeCell::WALL);
}

bool MazeCells::isUnconnected(Point p) {
    return isUnconnected(p.x, p.y);
}
