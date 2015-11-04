#ifndef MAZE_H
#define MAZE_H

#include <ncurses.h>
#include <string>

#include "ASCIIMazeRenderer.h"
#include "ColorMazeRenderer.h"
#include "DFSMazeGenerator.h"
#include "Dimension.h"
#include "Direction.h"
#include "EASCIIMazeRenderer.h"
#include "MazeCells.h"
#include "MazeGenerator.h"
#include "MazeRenderer.h"
#include "Point.h"
#include "ScrollView.h"

class Maze{
    MazeCells cells;
    Point currentPosition;
    Point end;
    const MazeRenderer* renderer;
    ScrollView viewport;

    void generate(bool animate, int animationDelay);

    Point getRandomUnvisitedDirection(Point p);
    bool tryMove(Point direction);

    static Dimension getScreenDimension() {
        Dimension d;
        getmaxyx(stdscr, d.height, d.width);
        return d;
    }

public:

    Maze (int w, int h, bool animate, int animationDelay);
    Maze (int w, int h, bool animate) : Maze(w,h,animate,50) {}
    Maze (int w, int h) : Maze(w,h,false,0) {}

    void render() {
        renderer->render(viewport.getDrawWindow(), cells, currentPosition, end);
        viewport.render();
    }

    bool win() {
        return end == currentPosition;
    }

    void setRenderer(MazeRenderer* r) {
        renderer = r;
    }

    //Pointer to const so that they can't render themselves or mess with anything, that's for us only
    //Really I just want them to be able to get the type
    //Maybe I'll do something else for that....
    //TODO type enumeration
    MazeRenderer const * getRenderer() {
        return renderer;
    }

    Point getCurrentPosition() { return currentPosition; }

    bool tryMoveUp() { 
        if (tryMove(Direction::UP)) {
            if (viewport.isVCenter(currentPosition + Point(0,2))) viewport.moveUp();
            return true;
        }
        return false;
    }
    bool tryMoveDown() {
        if (tryMove(Direction::DOWN)) {
            if (viewport.isVCenter(currentPosition)) viewport.moveDown();
            return true;
        }
        return false;
    }
    bool tryMoveLeft() {
        if (tryMove(Direction::LEFT)) {
            if (viewport.isHCenter(currentPosition + Point(2,0))) viewport.moveLeft();
            return true;
        }
        return false;
    }
    bool tryMoveRight() {
        if (tryMove(Direction::RIGHT)) {
            if (viewport.isHCenter(currentPosition)) viewport.moveRight();
            return true;
        }
        return false;
    }
};

#endif
