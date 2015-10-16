#ifndef MAZE_H
#define MAZE_H

#include <string>

#include "Direction.h"
#include "ColorMazeRenderer.h"
#include "MazeCells.h"
#include "MazeRenderer.h"
#include "Point.h"

class Maze{
    MazeCells cells;
    Point currentPosition;
    Point end;
    MazeRenderer* renderer = new ColorMazeRenderer();

    void generate(bool animate, int animationDelay);
    Point getRandomUnvisitedDirection(Point p);
    bool tryMove(Point direction);

public:

    Maze (int w, int h, bool animate, int animationDelay) : cells(2 * w + 1, 2 * h + 1) {
        end = Point(cells.getWidth() - 2, cells.getHeight() - 2);
        generate(animate, animationDelay);
        currentPosition = Point(1,1);
    }
    Maze (int w, int h, bool animate) : Maze(w,h,animate,50) {}
    Maze (int w, int h) : Maze(w,h,false,0) {}
    ~Maze() {
        delete renderer;
    }

    void render() {
        renderer->render(cells, currentPosition, end);
    }

    bool win() {
        return end == currentPosition;
    }

    Point getCurrentPosition() { return currentPosition; }

    bool tryMoveUp()    { return tryMove(Direction::UP);    }
    bool tryMoveDown()  { return tryMove(Direction::DOWN);  }
    bool tryMoveLeft()  { return tryMove(Direction::LEFT);  }
    bool tryMoveRight() { return tryMove(Direction::RIGHT); }
};

#endif
