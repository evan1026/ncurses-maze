#include "Maze.h"
#include "MazeCell.h"
#include "Point.h"

Maze::Maze(int _width, int _height) : width(2 * _width + 1), height(2 * _height + 1), cells(height, std::vector< MazeCell > (width, MazeCell())) {
    generate();
}

void Maze::initGrid() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i % 2 == 0 || j % 2 == 0) cells[i][j] = MazeCell(MazeCell::Type::WALL, MazeCell::Properties::P_NONE);
            else                          cells[i][j] = MazeCell(MazeCell::Type::OPEN, MazeCell::Properties::P_NONE);
        }
    }
}

void Maze::generate() {
    initGrid();
    //TODO The rest
}

MazeCell Maze::get(int x, int y) {
    if (x < width && x >= 0 && y < height && y >= 0) return cells[y][x];
    else                                             return MazeCell();
}

MazeCell Maze::get(Point p) {
    return get(p.x, p.y);
}

MazeCell Maze::getUpperNeighbor(int x, int y) {
    return get(x, y - 1);
}

MazeCell Maze::getUpperNeighbor(Point p) {
    return getUpperNeighbor(p.x, p.y);
}

MazeCell Maze::getLowerNeighbor(int x, int y) {
    return get(x, y + 1);
}

MazeCell Maze::getLowerNeighbor(Point p) {
    return getLowerNeighbor(p.x, p.y);
}

MazeCell Maze::getRightNeighbor(int x, int y) {
    return get(x + 1, y);
}

MazeCell Maze::getRightNeighbor(Point p) {
    return get(p.x, p.y);
}

MazeCell Maze::getLeftNeighbor(int x, int y) {
    return get(x - 1, y);
}

MazeCell Maze::getLeftNeighbor(Point p) {
    return get(p.x, p.y);
}
