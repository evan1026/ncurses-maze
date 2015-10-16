#ifndef MAZE_H
#define MAZE_H

#include <string>

#include "Direction.h"
#include "MazeCells.h"
#include "Point.h"

#define MAZE_COLOR_RED   1
#define MAZE_COLOR_BLUE  2
#define MAZE_COLOR_WHITE 3
#define MAZE_COLOR_GREEN 4
#define MAZE_COLOR_BLACK 5

class Maze{
    MazeCells cells;
    Point currentPosition;

    void generate(bool animate, int animationDelay);
    Point getRandomUnvisitedDirection(Point p);
    bool tryMove(Point direction);

public:

    Maze (int w, int h, bool animate, int animationDelay) : cells(2 * w + 1, 2 * h + 1) {
        start_color();
        init_pair(MAZE_COLOR_RED,   COLOR_BLACK, COLOR_RED);
        init_pair(MAZE_COLOR_BLUE,  COLOR_BLACK, COLOR_BLUE);
        init_pair(MAZE_COLOR_WHITE, COLOR_BLACK, COLOR_WHITE);
        init_pair(MAZE_COLOR_GREEN, COLOR_BLACK, COLOR_GREEN);
        init_pair(MAZE_COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
        generate(animate, animationDelay);
        currentPosition = Point(1,1);
    }
    Maze (int w, int h, bool animate) : Maze(w,h,animate,50) {}
    Maze (int w, int h) : Maze(w,h,false,0) {}

    void render();

    Point getCurrentPosition() { return currentPosition; }

    bool tryMoveUp()    { return tryMove(Direction::UP);    }
    bool tryMoveDown()  { return tryMove(Direction::DOWN);  }
    bool tryMoveLeft()  { return tryMove(Direction::LEFT);  }
    bool tryMoveRight() { return tryMove(Direction::RIGHT); }
};

#endif
