#ifndef CONSOLE_WINDOW_H
#define CONSOLE_WINDOW_H

#include <ncurses.h>

#include "CursesInstance.h"
#include "Point.h"

class ConsoleWindow {
    CursesInstance curses;
    WINDOW* window;

    int width;
    int height;
    int x;
    int y;

public:
    ConsoleWindow(int x, int y, int width, int height);
    ConsoleWindow(const ConsoleWindow& c);
    ConsoleWindow(ConsoleWindow&& c);
    ~ConsoleWindow();
    ConsoleWindow& operator=(const ConsoleWindow& c);
    ConsoleWindow& operator=(ConsoleWindow&& c);

    void set(int x, int y, chtype c);
    void set(Point p, chtype c);
    chtype get(int x, int y);
    chtype get(Point p);
    void drawBox();
    void refresh();

    int getWidth();
    int getHeight();
    int getX();
    int getY();
};
#endif
