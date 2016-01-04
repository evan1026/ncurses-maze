#include <iostream>
#include <vector>

#include "DFSMazeGenerator.h"
#include "Maze.h"
#include "MazeCell.h"
#include "MazeGenerator.h"
#include "MazeGeneratorType.h"
#include "Point.h"

Maze::Maze(int _width, int _height, MazeGeneratorType g) : width(2 * _width + 1), height(2 * _height + 1),
               start(1, 1), end(width - 2, height - 2), cells(height, std::vector< MazeCell > (width, MazeCell())),
               currentPosition(start) {
    generate(g);
}

Maze::Maze(int width, int height) : Maze(width, height, MazeGeneratorType::DFS) {}

void Maze::initGrid() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i % 2 == 0 || j % 2 == 0) cells[i][j] = MazeCell(MazeCell::Type::WALL, MazeCell::Properties::P_NONE);
            else                          cells[i][j] = MazeCell(MazeCell::Type::OPEN, MazeCell::Properties::P_NONE);
        }
    }
}

void Maze::generate(MazeGeneratorType g) {
    initGrid();

    MazeGenerator* generator;

    if (g == MazeGeneratorType::DFS) {
        generator = new DFSMazeGenerator();
    } else {
        std::cerr << "MazeGeneratorType not recognized in Maze.cpp line " << __LINE__ << std::endl;
        return;
    }

    generator->generate(*this);

    delete generator;
}

//Make sure to check bounds before calling
MazeCell& Maze::getRef(int x, int y) {
     return cells[y][x];
}

MazeCell& Maze::getRef(Point p) {
    return getRef(p.x, p.y);
}

MazeCell Maze::get(int x, int y) {
    if (x < width && x >= 0 && y < height && y >= 0) return getRef(x, y);
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

bool Maze::isUnconnected(Point p) {
    return isUnconnected(p.x, p.y);
}

bool Maze::isUnconnected(int x, int y) {
    return getUpperNeighbor(x, y).type == MazeCell::Type::WALL &&
           getLowerNeighbor(x, y).type == MazeCell::Type::WALL &&
           getRightNeighbor(x, y).type == MazeCell::Type::WALL &&
           getLeftNeighbor (x, y).type == MazeCell::Type::WALL;
}

Point Maze::getCurrentPosition() {
    return currentPosition;
}

void Maze::setType(int x, int y, MazeCell::Type t) {
    getRef(x, y).type = t;
}

void Maze::setType(Point p, MazeCell::Type t) {
    setType(p.x, p.y, t);
}

void Maze::setProperties(int x, int y, MazeCell::Properties pr) {
    getRef(x, y).properties = pr;
}

void Maze::setProperties(Point p, MazeCell::Properties pr) {
    setProperties(p.x, p.y, pr);
}
