#include <iostream>
#include <vector>

#include "DFSMazeGenerator.h"
#include "Maze.h"
#include "MazeCell.h"
#include "MazeGenerator.h"
#include "Point.h"
#include "PrimsMazeGenerator.h"
#include "Stats.h"

Maze::Maze(int _width, int _height, MazeGenerator::Type g) : modifiedPoints(), width(2 * _width + 1), height(2 * _height + 1),
               start(1, 1), end(width - 2, height - 2), cells(height, std::vector< MazeCell > (width, MazeCell())),
               currentPosition(start) {
    generate(g);
    setProperties(start, MazeCell::Properties::PART_OF_PATH);
}

Maze::Maze(int width, int height) : Maze(width, height, MazeGenerator::Type::PRIMS) {}

void Maze::initGrid() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x % 2 == 0 || y % 2 == 0) getRef(x,y) = MazeCell(MazeCell::Type::WALL, MazeCell::Properties::NONE);
            else                          getRef(x,y) = MazeCell(MazeCell::Type::OPEN, MazeCell::Properties::NONE);

            modifiedPoints.push(Point(x,y));
        }
    }
}

void Maze::generate(MazeGenerator::Type g) {
    initGrid();

    MazeGenerator* generator;

    if (g == MazeGenerator::Type::DFS) {
        generator = new DFSMazeGenerator();
    } else if (g == MazeGenerator::Type::PRIMS) {
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
    return getRightNeighbor(p.x, p.y);
}

MazeCell Maze::getLeftNeighbor(int x, int y) {
    return get(x - 1, y);
}

MazeCell Maze::getLeftNeighbor(Point p) {
    return getLeftNeighbor(p.x, p.y);
}

bool Maze::isUnconnected(Point p) {
    return isUnconnected(p.x, p.y);
}

//Unconnected means surrounded by walls (a cell on the edge is therefore not unconnected)
bool Maze::isUnconnected(int x, int y) {
    return getUpperNeighbor(x, y).type == MazeCell::Type::WALL &&
           getLowerNeighbor(x, y).type == MazeCell::Type::WALL &&
           getRightNeighbor(x, y).type == MazeCell::Type::WALL &&
           getLeftNeighbor (x, y).type == MazeCell::Type::WALL;
}

bool Maze::isConnected(Point p) {
    return isConnected(p.x, p.y);
}

//Connected means has an open cell next to it. A cell which is on the edge
//  and otherwise surrounded by walls is not connected
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
    modifiedPoints.push(Point(x,y));
}

void Maze::setType(Point p, MazeCell::Type t) {
    setType(p.x, p.y, t);
}

void Maze::setProperties(int x, int y, MazeCell::Properties pr) {
    getRef(x, y).properties = pr;
    modifiedPoints.push(Point(x,y));
}

void Maze::setProperties(Point p, MazeCell::Properties pr) {
    setProperties(p.x, p.y, pr);
}

bool Maze::move(Point p) {
    MazeCell cell = get(currentPosition + p);
    if (cell.type == MazeCell::Type::OPEN) {
        if (cell.properties == MazeCell::Properties::PART_OF_PATH) {
            setProperties(currentPosition, MazeCell::Properties::NOT_PART_OF_PATH);
            Stats::getInst().decrementOrCreateInt("pathLength");
            Stats::getInst().incrementOrCreateInt("wrongPathsLength");
        } else {
            Stats::getInst().incrementOrCreateInt("pathLength");
            if (cell.properties == MazeCell::Properties::NOT_PART_OF_PATH)
                Stats::getInst().decrementOrCreateInt("wrongPathsLength");
        }
        modifiedPoints.push(currentPosition);
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

Point Maze::popNextModifiedPoint() {
    Point out = Point(-1,-1);
    if (!modifiedPoints.empty()) {
        out = modifiedPoints.front();
        modifiedPoints.pop();
    }
    return out;
}

void Maze::refresh() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            modifiedPoints.push(Point(i,j));
        }
    }
}

void Maze::Solver::start() {
    maze.currentPosition = maze.start;

    for (int i = 0; i < maze.width; ++i) {
        for (int j = 0; j < maze.height; ++j) {
            maze.setProperties(i, j, MazeCell::Properties::NONE);
        }
    }
    maze.setProperties(maze.start, MazeCell::Properties::PART_OF_PATH);
    inprogress = true;
}

void Maze::Solver::stop() {
    inprogress = false;
}

void Maze::Solver::step() {
    MazeCell upper = maze.getUpperNeighbor(maze.currentPosition),
             lower = maze.getLowerNeighbor(maze.currentPosition),
             right = maze.getRightNeighbor(maze.currentPosition),
             left  = maze.getLeftNeighbor (maze.currentPosition);

    if (lower.type == MazeCell::Type::OPEN && lower.properties == MazeCell::Properties::NONE) {
        maze.moveDown();
    } else if (right.type == MazeCell::Type::OPEN && right.properties == MazeCell::Properties::NONE) {
        maze.moveRight();
    } else if (left.type == MazeCell::Type::OPEN && left.properties == MazeCell::Properties::NONE) {
        maze.moveLeft();
    } else if (upper.type == MazeCell::Type::OPEN && upper.properties == MazeCell::Properties::NONE) {
        maze.moveUp();
    } else {
        // need to backtrack
        if (lower.type == MazeCell::Type::OPEN && lower.properties == MazeCell::Properties::PART_OF_PATH) {
            maze.moveDown();
        } else if (right.type == MazeCell::Type::OPEN && right.properties == MazeCell::Properties::PART_OF_PATH) {
            maze.moveRight();
        } else if (left.type == MazeCell::Type::OPEN && left.properties == MazeCell::Properties::PART_OF_PATH) {
            maze.moveLeft();
        } else {
            maze.moveUp();
        }
    }
}

bool Maze::Solver::done() {
    return maze.currentPosition == maze.end;
}

bool Maze::Solver::inProgress() {
    return inprogress;
}
