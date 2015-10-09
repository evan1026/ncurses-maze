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
    pointStack.push(Point(1, 1));

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

void Maze::render() {
    Point cursorPos;
    getyx(stdscr, cursorPos.y, cursorPos.x);
    move(0,0);
    for (int y = 0; y < cells.getHeight(); ++y) {
        for (int x = 0; x < cells.getWidth(); ++x) {
            if (cells.getType(x,y) == MazeCell::Type::OPEN) {
                if (cells.getProperties(x,y) == MazeCell::Properties::PART_OF_PATH) {
                    attron(COLOR_PAIR(2));
                    printw(" ");
                    attroff(COLOR_PAIR(2));
                } else if (cells.getProperties(x,y) == MazeCell::Properties::NOT_PART_OF_PATH) {
                    attron(COLOR_PAIR(1));
                    printw(" ");
                    attroff(COLOR_PAIR(1));
                } else {
                    printw(" ");
                }
            } else {
                attron(COLOR_PAIR(3));
                printw(" ");
                attroff(COLOR_PAIR(3));
                /*MazeCell::Type up    = cells.upperNeighbor(x,y).type,
                               down  = cells.lowerNeighbor(x,y).type,
                               left  = cells.leftNeighbor(x,y).type,
                               right = cells.rightNeighbor(x,y).type;

                short flags = 0;
                if (up    == MazeCell::Type::WALL) flags |= 0b0001;
                if (down  == MazeCell::Type::WALL) flags |= 0b0010;
                if (left  == MazeCell::Type::WALL) flags |= 0b0100;
                if (right == MazeCell::Type::WALL) flags |= 0b1000;

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
                }*/
            }
        }
        printw("\n");
    }
    move(cursorPos.y, cursorPos.x);
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
        move(currentPosition.y, currentPosition.x);
        render();

        return true;
    }

    return false;
}
