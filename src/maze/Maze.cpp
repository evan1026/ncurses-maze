#include <chrono>
#include <ncurses.h>
#include <sstream>
#include <stack>
#include <thread>

#include "Direction.h"
#include "Maze.h"
#include "MazeCells.h"
#include "Point.h"

bool Maze::tryMove(Point direction) {
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
