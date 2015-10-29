#ifndef MAZE_H
#define MAZE_H

#include <string>

#include "ASCIIMazeRenderer.h"
#include "ColorMazeRenderer.h"
#include "DFSMazeGenerator.h"
#include "Direction.h"
#include "EASCIIMazeRenderer.h"
#include "MazeCells.h"
#include "MazeGenerator.h"
#include "MazeRenderer.h"
#include "Point.h"

class Maze{
    MazeCells cells;
    Point currentPosition;
    Point end;
    MazeRenderer* renderer;

    void generate(bool animate, int animationDelay) {
        MazeGenerator* g = new DFSMazeGenerator();
        g->generate(cells, renderer, animate, animationDelay);
        delete g;
    }

    Point getRandomUnvisitedDirection(Point p);
    bool tryMove(Point direction);

public:

    Maze (int w, int h, bool animate, int animationDelay) : cells(2 * w + 1, 2 * h + 1) {

        if (has_colors()) {
            renderer = new ColorMazeRenderer();
        } else {
            renderer = new EASCIIMazeRenderer(); //TODO see if ASCIIMazeRenderer is even needed
        }

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

    void setRenderer(MazeRenderer* r) {
        if (r != renderer) {
            delete renderer;
            renderer = r;
        }
    }

    //Pointer to const so that they can't render themselves or mess with anything, that's for us only
    //Really I just want them to be able to get the type
    //Maybe I'll do something else for that....
    //TODO type enumeration
    MazeRenderer const * getRenderer() {
        return renderer;
    }

    Point getCurrentPosition() { return currentPosition; }

    bool tryMoveUp()    { return tryMove(Direction::UP);    }
    bool tryMoveDown()  { return tryMove(Direction::DOWN);  }
    bool tryMoveLeft()  { return tryMove(Direction::LEFT);  }
    bool tryMoveRight() { return tryMove(Direction::RIGHT); }
};

#endif
