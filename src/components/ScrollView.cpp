#include <ncurses.h>
#include <sstream>

#include "Dimension.h"
#include "ScrollView.h"

ScrollView::ScrollView(Dimension out, int innerWidth, int innerHeight, MazeRenderer* r) : 
        d(out), in_d(0, 0, innerWidth, innerHeight), renderer(r) {
    window = newwin(d.height, d.width, d.y, d.x);
    innerWindow = newwin(in_d.height, in_d.width, in_d.y, in_d.x);
}

void ScrollView::render(MazeCells& m, Point currentPosition, Point end) {
    renderer->render(innerWindow, m, currentPosition, end);
    center(currentPosition);

    int startx = 0, starty = 0, width = d.width, height = d.height;

    if (needsBorder()) {
        ++startx;
        ++starty;
        --width;
        --height;
        box(window, 0, 0); //TODO Draw my own box to correspond with the inner window better
    }

    for (int y = starty; y < height; ++y) {
        for (int x = startx; x < width; ++x) {
            int iny = y - starty + in_d.y;
            int inx = x - startx + in_d.x;
            
            if (iny >= 0 && iny < in_d.height && inx >= 0 && inx < in_d.width) {
                chtype c = mvwinch(innerWindow, iny, inx);
                mvwaddch(window, y, x, c);
            }
        }
    }

    wrefresh(window);
}

void ScrollView::center(Point position) {
    int x = 0,
        y = 0;

    if (needsBorder()) {
        x = position.x - (d.width - 2) / 2;
        y = position.y - (d.height - 2) / 2;

        move(10,50);
        clrtoeol();
        printw("Orignial x:  %d", x);
        move(11, 50);
        clrtoeol();
        printw("Original y:  %d", y);

        if (x > in_d.width - (d.width - 2)) x = in_d.width - (d.width - 2);
        if (y > in_d.height - (d.height - 2)) y = in_d.height - (d.height - 2);

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        
        move(12,50);
        clrtoeol();
        printw("Corrected x: %d", x);
        move(13, 50);
        clrtoeol();
        printw("Corrected y: %d", y);
    }

    in_d.x = x;
    in_d.y = y;
}
