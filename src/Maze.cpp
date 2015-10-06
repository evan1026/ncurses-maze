#include <sstream>
#include <stack>
#include <ncurses.h>
#include <chrono>
#include <thread>

#include "MazeCells.h"
#include "Maze.h"
#include "Point.h"

void Maze::generate(bool animate, int animationDelay) {

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

        //clear();
        if (!pointStack.empty() && animate) {
            Point cursorPos = pointStack.top();
            render();
            move(cursorPos.y, cursorPos.x);
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

void Maze::render() {
    Point cursorPos;
    getyx(stdscr, cursorPos.y, cursorPos.x);
    move(0,0);
    for (int y = 0; y < cells.getHeight(); ++y) {
        for (int x = 0; x < cells.getWidth(); ++x) {
            if (cells.get(x,y) == MazeCell::OPEN) printw(" ");
            else {
                MazeCell up    = cells.upperNeighbor(x,y),
                         down  = cells.lowerNeighbor(x,y),
                         left  = cells.leftNeighbor(x,y),
                         right = cells.rightNeighbor(x,y);

                short flags = 0;
                if (up    == MazeCell::WALL) flags |= 0b0001;
                if (down  == MazeCell::WALL) flags |= 0b0010;
                if (left  == MazeCell::WALL) flags |= 0b0100;
                if (right == MazeCell::WALL) flags |= 0b1000;

                switch (flags) {
                    case 0b1111:
                        addch(ACS_PLUS);
                        break;
                    case 0b1110:
                        addch(ACS_TTEE);
                        break;
                    case 0b1101:
                        addch(ACS_BTEE);
                        break;
                    case 0b1011:
                        addch(ACS_LTEE);
                        break;
                    case 0b0111:
                        addch(ACS_RTEE);
                        break;
                    case 0b1100:
                        addch(ACS_HLINE);
                        break;
                    case 0b1010:
                        addch(ACS_ULCORNER);
                        break;
                    case 0b1001:
                        addch(ACS_LLCORNER);
                        break;
                    case 0b0110:
                        addch(ACS_URCORNER);
                        break;
                    case 0b0101:
                        addch(ACS_LRCORNER);
                        break;
                    case 0b0011:
                        addch(ACS_VLINE);
                        break;
                    case 0b1000:
                        addch(ACS_HLINE);
                        break;
                    case 0b0100:
                        addch(ACS_HLINE);
                        break;
                    case 0b0010:
                        addch(ACS_VLINE);
                        break;
                    case 0b0001:
                        addch(ACS_VLINE);
                        break;
                    case 0b0000:
                        printw("!"); //because it shouldn't happen
                        break;
                    default:
                        printw("?"); //because it really shouldn't happen
                        break;
                }
            }
        }
        printw("\n");
    }
    move(cursorPos.y, cursorPos.x);
}
