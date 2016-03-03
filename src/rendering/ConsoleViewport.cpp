#include <ncurses.h>

#include "ConsoleViewport.h"
#include "Dimension.h"
#include "Point.h"

ConsoleViewport::ConsoleViewport(Dimension d, int innerWidth, int innerHeight) :
            innerWindow(innerWidth, innerHeight),
            containerWindow(d.x, d.y, d.width, d.height) {
    shrinkToFit();
}

void ConsoleViewport::centerOn(Point p) {
    int x = 0,
        y = 0;

    int innerWidth  = innerWindow.getWidth(),
        innerHeight = innerWindow.getHeight(),
        width       = containerWindow.getWidth(),
        height      = containerWindow.getHeight();

    if (needsBorder()) {
        width = width - 2;
        height = height - 2;

        x = width / 2 - p.x;
        y = height / 2 - p.y;

        if (x > 0)  x = 0;
        if (y > 0)  y = 0;

        if (innerWidth > width) {
            if (x < width - innerWidth) x = width - innerWidth;
        } else {
            x = 0;
        }

        if (innerHeight > height) {
           if (y < height - innerHeight) y = height - innerHeight;
        } else {
            y = 0;
        }
    }

    innerWindowX = x;
    innerWindowY = y;
}

void ConsoleViewport::centerOn(int x, int y) {
    centerOn(Point(x,y));
}

void ConsoleViewport::set(int x, int y, chtype c) {
    innerWindow.set(x, y, c);
}

void ConsoleViewport::set(Point p, chtype c) {
    set(p.x, p.y, c);
}

chtype ConsoleViewport::get(int x, int y) {
    return innerWindow.get(x, y);
}

chtype ConsoleViewport::get(Point p) {
    return get(p.x, p.y);
}

void ConsoleViewport::refresh() {
    int startx = 0,
        starty = 0,
        width = containerWindow.getWidth(),
        height = containerWindow.getHeight();

    if (needsBorder()) {
        ++startx;
        ++starty;
        width -= 2;
        height -= 2;
        containerWindow.drawBox();
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int innerX = x - innerWindowX;
            int innerY = y - innerWindowY;

            if (innerX >= 0 && innerX < innerWindow.getWidth() && innerY >= 0 && innerY < innerWindow.getHeight()) {
                containerWindow.set(x + startx, y + starty, innerWindow.get(innerX, innerY));
            } else {
                containerWindow.set(x + startx, y + starty, '!');
            }
        }
    }
    containerWindow.refresh();
}

void ConsoleViewport::resize(Dimension d) {
    containerWindow = ConsoleWindow(d.x, d.y, d.width, d.height);
}

void ConsoleViewport::shrinkToFit() {
    int newWidth = containerWindow.getWidth(),
        newHeight = containerWindow.getHeight();

    if (innerWindow.getWidth() < newWidth)
        newWidth = innerWindow.getWidth();
    if (innerWindow.getHeight() < newHeight)
        newHeight = innerWindow.getHeight();

    if (newWidth == innerWindow.getWidth() && newHeight < innerWindow.getHeight()) {
        int roomToGrow = containerWindow.getWidth() - newWidth;
        if      (roomToGrow < 0) roomToGrow = 0;
        else if (roomToGrow > 2) roomToGrow = 2;
        newWidth += roomToGrow;
    } else if (newHeight == innerWindow.getHeight() && newWidth < innerWindow.getWidth()) {
        int roomToGrow = containerWindow.getHeight() - newHeight;
        if      (roomToGrow < 0) roomToGrow = 0;
        else if (roomToGrow > 2) roomToGrow = 2;
        newHeight += roomToGrow;
    }

    if (newWidth != containerWindow.getWidth() || newHeight != containerWindow.getHeight())
        containerWindow = ConsoleWindow(containerWindow.getX(), containerWindow.getY(), newWidth, newHeight);
}
