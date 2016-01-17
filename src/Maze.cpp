#include <iostream>
#include <vector>

#include "DFSMazeGenerator.h"
#include "Maze.h"
#include "MazeCell.h"
#include "MazeGenerator.h"
#include "MazeGeneratorType.h"
#include "Point.h"
#include "PrimsMazeGenerator.h"

Maze::Maze(int _width, int _height, MazeGeneratorType g) : width(2 * _width + 1), height(2 * _height + 1),
               start(1, 1), end(width - 2, height - 2), cells(height, std::vector< MazeCell > (width, MazeCell())),
               currentPosition(start) {
    generate(g);
    setProperties(start, MazeCell::Properties::PART_OF_PATH);
}

Maze::Maze(int width, int height) : Maze(width, height, MazeGeneratorType::PRIMS) {}

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
    } else if (g == MazeGeneratorType::PRIMS) {
        generator = new PrimsMazeGenerator();
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

bool Maze::isConnected(Point p) {
    return isConnected(p.x, p.y);
}

bool Maze::isConnected(int x, int y) {
    return getUpperNeighbor(x, y).type == MazeCell::Type::OPEN ||
           getLowerNeighbor(x, y).type == MazeCell::Type::OPEN ||
           getRightNeighbor(x, y).type == MazeCell::Type::OPEN ||
           getLeftNeighbor (x, y).type == MazeCell::Type::OPEN;
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

bool Maze::move(Point p) {
    MazeCell cell = get(currentPosition + p);
    if (cell.type == MazeCell::Type::OPEN) {
        if (cell.properties == MazeCell::Properties::PART_OF_PATH) {
            setProperties(currentPosition, MazeCell::Properties::NOT_PART_OF_PATH);
        }
        currentPosition += p;
        setProperties(currentPosition, MazeCell::Properties::PART_OF_PATH);
        return true;
    }
    return false;
}

bool Maze::moveUp() {
    return move(Point(0,-1));
}

bool Maze::moveDown() {
    return move(Point(0,1));
}

bool Maze::moveLeft() {
    return move(Point(-1,0));
}

bool Maze::moveRight() {
    return move(Point(1,0));
}
