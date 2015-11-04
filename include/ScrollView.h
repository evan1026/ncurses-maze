#ifndef SCROLL_VIEW_H
#define SCROLL_VIEW_H

#include <ncurses.h>
#include <sstream>

#include "Dimension.h"
#include "Point.h"

class ScrollView {
    WINDOW* window;
    WINDOW* innerWindow;
    Dimension d, in_d;

public:
    ScrollView(Dimension out, int innerWidth, int innerHeight);
    ScrollView() {
        window = NULL;
        innerWindow = NULL;
    }
    ~ScrollView() {
        if (window != NULL) {
            delwin(window);
        }
        if (innerWindow != NULL) {
            delwin(innerWindow);
        }
    }

    bool isHCenter(Point p) {
        return p.x - in_d.x == d.width / 2;
    }
    bool isVCenter(Point p) {
        return p.y - in_d.y == d.height / 2;
    }

    void render();

    void set(int y, int x, chtype ch) {
        mvwaddch(innerWindow, y, x, ch);
    }

    bool needsBorder() {
        return in_d.width > d.width || in_d.height > d.height;
    }

    void moveLeft() {
        if (needsBorder() && in_d.x > 0) in_d.x--;
        render();
    }
    void moveRight() {
        if (needsBorder() && in_d.x < in_d.width - (d.width - 2)) in_d.x++;
        render();
    }
    void moveUp() {
        if (needsBorder() && in_d.y > 0) in_d.y--;
        render();
    }
    void moveDown() {
        if (needsBorder() && in_d.y < in_d.height - (d.height - 2)) in_d.y++;
        render();
    }

    WINDOW* getDrawWindow() {
        return innerWindow;
    }
};

#endif
