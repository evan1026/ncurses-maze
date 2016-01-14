#ifndef PSEUDO_CONSOLE_WINDOW_H
#define PSEUDO_CONSOLE_WINDOW_H

#include <ncurses.h>
#include <vector>

#include "Point.h"

//Not meant to be displayed, just written to and read from
class PseudoConsoleWindow {

    int width;
    int height;
    std::vector< std::vector< chtype > > cells;

public:
    PseudoConsoleWindow(int width, int height);

    void set(int x, int y, chtype c);
    void set(Point p, chtype c);
    chtype get(int x, int y);
    chtype get(Point p);

    int getWidth();
    int getHeight();
};

#endif
