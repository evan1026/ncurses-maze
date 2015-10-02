#include <string>
#include <sstream>
#include <iostream>
#include <list>

#include "MazeCells.h"
#include "Maze.h"
#include "Point.h"

//Should probably be split into many functions
//TODO Split into many functions
//I probably won't though
void Maze::generate() {
    
    //TODO
    //TODO Make stack implementation
    //TODO https://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search
    //TODO

    Point end(2 * width - 1, 2 * height - 1);
    
    std::list<Point> endpoints;
    std::list<Point> foundPoints;
    endpoints.push_back(Point(1,1));
    foundPoints.push_back(Point(1,1));

    Point directions[] = {Point(-1,  0),
                          Point( 1,  0),
                          Point( 0, -1),
                          Point( 0,  1)};

    srand(time(NULL));

    bool done = false;
    while (!done) {

        int randNum = rand() % (endpoints.size());
        Point p;
        for (std::list<Point>::iterator i = endpoints.begin(); i != endpoints.end(); ++i) {
            if (randNum-- == 0) {
                p = *i;
                break;
            }
        }

        randNum = rand() % (4 + 10); //4 -> number of directions.

        if (randNum < 4) { //If we're moving
            Point wallInBetween = p + directions[randNum];
            Point destCell = wallInBetween + directions[randNum];
            if (cells.get(wallInBetween) == MazeCell::WALL //If we're next to a wall
                    && cells.get(destCell) == MazeCell::OPEN //And we're not going off the map
                    && cells.isUnconnected(destCell)) { //And we haven't been here before
                cells.set(wallInBetween, MazeCell::OPEN); //Open up the wall in between
                endpoints.push_back(destCell);
                foundPoints.push_back(destCell);
            }
        }
           
        if (foundPoints.size() == width * height && !cells.isUnconnected(end)) {
            done = true;
        } else { //if we're not done, let's remove the points we can't move from to make it quicker
            for (std::list<Point>::iterator i = endpoints.begin(); i != endpoints.end(); ++i) {
                Point leftNC  = *i + Point(-2, 0); //NC = neighbor cell, as opposed to a simple neighbor, which is always a wall
                Point rightNC = *i + Point( 2, 0);
                Point upNC    = *i + Point( 0,-2);
                Point downNC  = *i + Point( 0, 2);

                //Each of the next 4 lines determines if we can get to one of the neighbors
                //Whole thing says if we can't move to any neighbor, remove this one from list of possibilities
                if (!(cells.get(leftNC)  == MazeCell::OPEN && cells.isUnconnected(leftNC))  &&
                    !(cells.get(rightNC) == MazeCell::OPEN && cells.isUnconnected(rightNC)) &&
                    !(cells.get(upNC)    == MazeCell::OPEN && cells.isUnconnected(upNC))    &&
                    !(cells.get(downNC)  == MazeCell::OPEN && cells.isUnconnected(downNC))) {
                       i = endpoints.erase(i);
                       --i;
                }
            }
        }
    }
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
