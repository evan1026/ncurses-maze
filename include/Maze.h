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
    ScrollView viewport;

    void generate(bool animate, int animationDelay);

    Point getRandomUnvisitedDirection(Point p);
    bool tryMove(Point direction);

    static Dimension getScreenDimension() {
        Dimension d(0,0,20,20);
        //getmaxyx(stdscr, d.height, d.width);
        return d;
    }

    static MazeRenderer* getRenderer() {
        if (has_colors()) {
            return ColorMazeRenderer::getInstance();
        } else {
            return EASCIIMazeRenderer::getInstance(); //TODO see if ASCIIMazeRenderer is even needed
        }
    }

public:

    Maze (int w, int h, bool animate, int animationDelay);
    Maze (int w, int h, bool animate) : Maze(w,h,animate,50) {}
    Maze (int w, int h) : Maze(w,h,false,0) {}

    void render() {
        viewport.render(cells, currentPosition, end);
    }

    void renderp(Point position) {
        currentPosition = position;
        render();
    }

    bool win() {
        return end == currentPosition;
    }

    Point getCurrentPosition() { return currentPosition; }

    bool tryMoveUp() { 
        return tryMove(Direction::UP);
    }
    bool tryMoveDown() {
        return tryMove(Direction::DOWN);
    }
    bool tryMoveLeft() {
        return tryMove(Direction::LEFT);
    }
    bool tryMoveRight() {
        return tryMove(Direction::RIGHT);
    }

    void adjustViewport(int width, int height) {
        viewport.resize(width, height);
    }

    void handleSizeChanged() {
        endwin();
        refresh();
        clear();

        Point p;
        getmaxyx(stdscr, p.y, p.x);
        adjustViewport(p.x, p.y);
        render();
    }
};

#endif
