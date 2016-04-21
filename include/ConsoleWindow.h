#ifndef CONSOLE_WINDOW_H
#define CONSOLE_WINDOW_H

#include <ncurses.h>

#include "CursesInstance.h"
#include "Point.h"

/**************************************************************************
 * ~~~~~~~~~~~~~~~~~                                                      *
 * ~ ConsoleWindow ~                                                      *
 * ~~~~~~~~~~~~~~~~~                                                      *
 *                                                                        *
 * This class represents a window that is drawn to the console. It also   *
 * serves as a wrapper for the primitive ncurses WINDOW, and will         *
 * handle managing the memory for the window as well as writing to and    *
 * reading from it. Most of these functions simply forward to the         *
 * CursesInstance, which wraps the ncurses C functions.                   *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

class ConsoleWindow {
    CursesInstance curses;
    WINDOW* window;

    int width,
        height,
        x,
        y;

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
