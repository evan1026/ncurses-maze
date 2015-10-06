#include <sstream>
#include <stack>

/* Uncomment along with later lines to see maze generation in action */
//#include <iostream>

#include "MazeCells.h"
#include "Maze.h"
#include "Point.h"

void Maze::generate() {

    srand(time(NULL));

    std::stack<Point> pointStack;
    pointStack.push(Point(1,1));

    while (!pointStack.empty()) {
        Point p = pointStack.top();
        Point neighborDirection = getRandomUnvisitedDirection(p);
        if (neighborDirection == Point(0,0)) { //All neighbors visited
            pointStack.pop();
        } else {
            Point wallInBetween = p + neighborDirection;
            Point destCell = wallInBetween + neighborDirection;
            cells.set(wallInBetween, MazeCell::OPEN);
            pointStack.push(destCell);
        }

        /* Uncomment to see the maze generation in action */
        //std::cout << render() << std::endl;
        //std::cin.get();
    }
}


//Randomly selects an unvisited neighbor to the cell at point p
//Assumes PRNG has already been initialized (srand already called)
//Returns (0,0) when no unvisited neighbor exists
//Returns the direction to move to get to the unvisited neighbor
Point Maze::getRandomUnvisitedDirection(Point p) {
    //Directions don't change, and they're only needed here, so make
    //them static to the function itself
    static Point directions[] = {Point(-1,  0),
                                 Point( 1,  0),
                                 Point( 0, -1),
                                 Point( 0,  1)};

    short directionIndex = rand() % 4;
    short attempts = 0;

    //Cool thing about isUnconnected is it inadvertently makes sure we don't go off the edge as well
    while (!cells.isUnconnected(p + 2 * directions[directionIndex]) && attempts < 4) {
        directionIndex = (directionIndex + 1) % 4;
        attempts++;
    }

    if (attempts == 4)
        return Point(0,0);

    return directions[directionIndex];

}

std::string Maze::render() {
    std::stringstream ss;
    for (int y = 0; y < cells.getHeight(); ++y) {
        for (int x = 0; x < cells.getWidth(); ++x) {
            if (cells.get(x,y) == MazeCell::OPEN) ss << " ";
            else {
                MazeCell up    = cells.upperNeighbor(x,y),
                         down  = cells.lowerNeighbor(x,y),
                         left  = cells.leftNeighbor(x,y),
                         right = cells.rightNeighbor(x,y);

                if (right == MazeCell::WALL || left == MazeCell::WALL) {
                    if (up == MazeCell::WALL || down == MazeCell::WALL) {
                        ss << "+";
                    } else {
                        ss << "-";
                    }
                } else {
                    if (up == MazeCell::WALL || down == MazeCell::WALL) {
                        ss << "|";
                    } else {
                        ss << " ";
                    }
                }
            }
        }
        ss << "\n";
    }

    return ss.str();
}
