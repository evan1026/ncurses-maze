#include <ncurses.h>
#include <sstream>

#include "Dimension.h"
#include "ScrollView.h"

ScrollView::ScrollView(Dimension out, int innerWidth, int innerHeight) : 
        d(out), in_d(0, 0, innerWidth, innerHeight) {
    window = newwin(d.height, d.width, d.y, d.x);
    innerWindow = newwin(in_d.height, in_d.width, in_d.y, in_d.x);
}

void ScrollView::render() {
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
