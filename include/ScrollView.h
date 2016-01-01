#ifndef SCROLL_VIEW_H
#define SCROLL_VIEW_H

#include <ncurses.h>

#include "Dimension.h"
#include "Point.h"
#include "MazeCells.h"
#include "MazeRenderer.h"

class ScrollView {
    WINDOW* window;
    WINDOW* innerWindow;
    Dimension d, in_d;
    MazeRenderer* renderer;

    bool needsBorder() {
        return in_d.width > d.width || in_d.height > d.height;
    }

    void center(Point position);

public:
    ScrollView(Dimension out, int innerWidth, int innerHeight, MazeRenderer* r);
    ~ScrollView() {
        if (window != NULL) {
            delwin(window);
        }
        if (innerWindow != NULL) {
            delwin(innerWindow);
        }
    }

    void render(MazeCells& m, Point currentPosition, Point end);

    void resize(int width, int height) {
        d.width = width;
        d.height = height;

        wresize(window, height, width);
    }
};

#endif
