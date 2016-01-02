#ifndef CONSOLE_WINDOW_H
#define CONSOLE_WINDOW_H

#include <ncurses.h>

#include "Point.h"

class ConsoleWindow {
    WINDOW* window;

public:
    const int width;
    const int height;
    const int x;
    const int y;

    ConsoleWindow(int x, int y, int width, int height);
    ~ConsoleWindow();
    
    void set(int x, int y, chtype c);
    void set(Point p, chtype c);
    chtype get(int x, int y);
    chtype get(Point p);
    void drawBox();
    void refresh();
    void init();
};

#endif
