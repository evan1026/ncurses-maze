#ifndef CONSOLE_VIEWPORT_H
#define CONSOLE_VIEWPORT_H

#include <ncurses.h>

#include "ConsoleWindow.h"
#include "Dimension.h"
#include "Point.h"
#include "PseudoConsoleWindow.h"

class ConsoleViewport {
    PseudoConsoleWindow innerWindow;
    ConsoleWindow containerWindow;
    int innerWindowX = 0,
        innerWindowY = 0;

    bool needsBorder() {
        return innerWindow.getWidth() > containerWindow.getWidth() ||
               innerWindow.getHeight() > containerWindow.getHeight();
    }

public:
    ConsoleViewport(Dimension dimension, int innerWidth, int innerHeight);

    void centerOn(Point position);
    void centerOn(int x, int y);

    void set(int x, int y, chtype c);
    void set(Point p, chtype c);

    chtype get(int x, int y);
    chtype get(Point p);

    void refresh();
    void resize(Dimension dimension);
};

#endif
