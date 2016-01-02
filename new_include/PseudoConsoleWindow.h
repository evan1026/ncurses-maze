#ifndef PSEUDO_CONSOLE_WINDOW_H
#define PSEUDO_CONSOLE_WINDOW_H

#include <ncurses.h>
#include <vector>

#include "Point.h"

//Not meant to be displayed, just written to and read from
class PseudoConsoleWindow {

public:
    const int width;
    const int height;
    PseudoConsoleWindow(int width, int height);
    
    void set(int x, int y, chtype c);
    void set(Point p, chtype c);
    chtype get(int x, int y);
    chtype get(Point p);
    
private:
    std::vector< std::vector< chtype > > cells; //Declared later so it's initialized after width and height
};

#endif
