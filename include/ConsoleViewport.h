#ifndef CONSOLE_VIEWPORT_H
#define CONSOLE_VIEWPORT_H

#include <ncurses.h>

#include "ConsoleWindow.h"
#include "Dimension.h"
#include "Point.h"
#include "PseudoConsoleWindow.h"

/**************************************************************************
 * ~~~~~~~~~~~~~~~~~~~                                                    *
 * ~ ConsoleViewport ~                                                    *
 * ~~~~~~~~~~~~~~~~~~~                                                    *
 *                                                                        *
 * This class acts as a scrollable window that holds the maze. If the     *
 * maze is too large to fit entirely on screen, this class will handle    *
 * mapping a point on the maze to a point on the screen given an offset   *
 * to make sure the player cursor is always in the center, or the egde of *
 * the maze is at the edge of the screen, depending on the exact position *
 * of the cursor.                                                         *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

class ConsoleViewport {
    PseudoConsoleWindow innerWindow; //This is the inner window that holds the whole maze
    ConsoleWindow containerWindow; //This is the outer window that fills the screen
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

    void shrinkToFit();
};

#endif
