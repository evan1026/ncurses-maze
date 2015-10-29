#include <chrono>
#include <ncurses.h>
#include <sstream>
#include <stack>
#include <thread>

#include "DFSMazeGenerator.h"
#include "Direction.h"
#include "MazeCells.h"
#include "Point.h"

void DFSMazeGenerator::generate(MazeCells& m, MazeRenderer* r, bool animate, int animationDelay) {

    Point end = Point(m.getWidth() - 2, m.getHeight() - 2);
    Point currentPosition = end;

    srand(time(NULL));

    std::stack<Point> pointStack;
    pointStack.push(end);

    while (!pointStack.empty()) {
        Point p = pointStack.top();
        Point neighborDirection = getRandomUnvisitedDirection(p, m);
        if (neighborDirection == Point(0, 0)) { //All neighbors visited
            pointStack.pop();
        } else {
            Point wallInBetween = p + neighborDirection;
            Point destCell = wallInBetween + neighborDirection;
            m.setType(wallInBetween, MazeCell::Type::OPEN);
            pointStack.push(destCell);
        }

        if (!pointStack.empty() && animate) {
            currentPosition = pointStack.top();
            r->render(m, currentPosition, end);
            std::this_thread::sleep_for(std::chrono::milliseconds(animationDelay));
        }
    }
}

//Randomly selects an unvisited neighbor to the cell at point p
//Assumes PRNG has already been initialized (srand already called)
//Returns (0,0) when no unvisited neighbor exists
//Returns the direction to move to get to the unvisited neighbor
Point DFSMazeGenerator::getRandomUnvisitedDirection(Point p, MazeCells& cells) {

    short directionIndex = rand() % 4;
    short attempts = 0;

    //Cool thing about isUnconnected is it also makes sure we don't go off the edge as well
    while (!cells.isUnconnected(p + 2 * Direction::directions[directionIndex]) && attempts < 4) {
        directionIndex = (directionIndex + 1) % 4;
        attempts++;
    }

    if (attempts == 4)
        return Point(0,0);

    return Direction::directions[directionIndex];

}
