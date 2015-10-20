#include <sstream>
#include <stack>
#include <ncurses.h>
#include <chrono>
#include <thread>

#include "Direction.h"
#include "MazeCells.h"
#include "Maze.h"
#include "Point.h"

void Maze::generate(bool animate, int animationDelay) {

    srand(time(NULL));

    std::stack<Point> pointStack;
    pointStack.push(end);

    while (!pointStack.empty()) {
        Point p = pointStack.top();
        Point neighborDirection = getRandomUnvisitedDirection(p);
        if (neighborDirection == Point(0, 0)) { //All neighbors visited
            pointStack.pop();
        } else {
            Point wallInBetween = p + neighborDirection;
            Point destCell = wallInBetween + neighborDirection;
            cells.setType(wallInBetween, MazeCell::Type::OPEN);
            pointStack.push(destCell);
        }

        if (!pointStack.empty() && animate) {
            currentPosition = pointStack.top();
            render();
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(animationDelay));
        }
    }
}


//Randomly selects an unvisited neighbor to the cell at point p
//Assumes PRNG has already been initialized (srand already called)
//Returns (0,0) when no unvisited neighbor exists
//Returns the direction to move to get to the unvisited neighbor
Point Maze::getRandomUnvisitedDirection(Point p) {

    short directionIndex = rand() % 4;
    short attempts = 0;

    //Cool thing about isUnconnected is it inadvertently makes sure we don't go off the edge as well
    while (!cells.isUnconnected(p + 2 * Direction::directions[directionIndex]) && attempts < 4) {
        directionIndex = (directionIndex + 1) % 4;
        attempts++;
    }

    if (attempts == 4)
        return Point(0,0);

    return Direction::directions[directionIndex];

}

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
