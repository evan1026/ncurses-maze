#ifndef PSEUDO_CONSOLE_WINDOW_H
#define PSEUDO_CONSOLE_WINDOW_H

#include <ncurses.h>
#include <vector>

#include "Point.h"

/**************************************************************************
 * ~~~~~~~~~~~~~~~~~~~~~~~                                                *
 * ~ PseudoConsoleWindow ~                                                *
 * ~~~~~~~~~~~~~~~~~~~~~~~                                                *
 *                                                                        *
 * A collection of chtype's that acts like a console window (in that it   *
 * can be written to and read from) but is not actually displayed. This   *
 * is meant to serve as a buffer to the actual console.                   *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

class PseudoConsoleWindow {
    int width,
        height;
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
