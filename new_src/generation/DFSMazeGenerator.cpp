#include <cstdlib>
#include <ctime>
#include <stack>

#include "DFSMazeGenerator.h"
#include "Maze.h"
#include "MazeGenerator.h"
#include "Point.h"

Point DFSMazeGenerator::getRandomUnvisitedDirection(Maze& m, Point p) {

    static Point directions[] = {Point(1,0), Point(-1,0), Point(0,1), Point(0,-1)};

    short directionIndex = rand() % 4;
    short attempts = 0;

    while (!m.isUnconnected(p + 2 * directions[directionIndex]) && attempts < 4) {
        directionIndex = (directionIndex + 1) % 4;
        ++attempts;
    }

    if (attempts == 4)
        return Point(0, 0);

    return directions[directionIndex];
}

void DFSMazeGenerator::generate(Maze& m) {

    Point current = m.end;

    srand(time(NULL));

    std::stack<Point> pointStack;
    pointStack.push(current);

    while(!pointStack.empty()) {
        Point p = pointStack.top();
        Point neighborDirection = getRandomUnvisitedDirection(m, p);
        if (neighborDirection == Point(0, 0)) {
            pointStack.pop();
        } else {
            Point wall = p + neighborDirection;
            Point dest = wall + neighborDirection;
            m.setType(wall, MazeCell::Type::OPEN);
            pointStack.push(dest);
        }
    }
}
