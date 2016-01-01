#include <chrono>
#include <ncurses.h>
#include <sstream>
#include <stack>
#include <thread>

#include "Direction.h"
#include "Maze.h"
#include "MazeCells.h"
#include "Point.h"

Maze::Maze(int w, int h, bool animate, int animationDelay) :
        cells(2 * w + 1, 2 * h + 1), viewport(getScreenDimension(), 2 * w + 1, 2 * h + 1, getRenderer()) {

    end = Point(cells.getWidth() - 2, cells.getHeight() - 2);
    generate(animate, animationDelay);
    currentPosition = Point(1,1);
}

void Maze::generate(bool animate, int animationDelay) {
    std::function<void(Point)> f = std::bind(&Maze::renderp, this, std::placeholders::_1);
    MazeGenerator* g = new DFSMazeGenerator();
    g->generate(cells, f, animate, animationDelay);
    delete g;
}

bool Maze::tryMove(Point direction) {
    //TODO canMove to make tryMoves make more sense
    if (cells.getType(currentPosition + direction) == MazeCell::Type::OPEN) {
        if (cells.getProperties(currentPosition + direction) == MazeCell::Properties::PART_OF_PATH) { //backtracking
            cells.setProperties(currentPosition, MazeCell::Properties::NOT_PART_OF_PATH);
        } else if (cells.getProperties(currentPosition + direction) == MazeCell::Properties::P_NONE) {
            cells.setProperties(currentPosition, MazeCell::Properties::PART_OF_PATH); //a little redundant; ensures starting point is highlighted too
        }

        currentPosition += direction;
        cells.setProperties(currentPosition, MazeCell::Properties::PART_OF_PATH);

        render();

        return true;
    }

    return false;
}
