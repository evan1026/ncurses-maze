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
        box(window, 0, 0);
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

    /*********************************************************
     *    What follows was attempted code for scroll bars    *
     * I gave up on them because they looked dumb and didn't *
     *             really work correctly anyway.             *
     *   I'm leaving this in for one commit just in case I   *
     *              want to revisit this later.              *
     ********************************************************/

    /*
    int hbarWidth  = std::max(1, (int)(((float) d.width / (float) in_d.width) * (d.width - 2)));
    int vbarHeight = std::max(1, (int)(((float) d.height / (float) in_d.height) * (d.height - 2)));

    int hbarStart = (int)(((float) in_d.x / (float) in_d.width) * (d.width - 2)) + 1;
    int vbarStart = (int)(((float) in_d.y / (float) in_d.height) * (d.height - 2)) + 1;

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_RED);

    for (int i = 1; i < d.width - 1; ++i) {
        if (i >= hbarStart && i < hbarStart + hbarWidth) {
            wmove(window, d.height - 1, i);
            wattron(window, COLOR_PAIR(2));
            waddch(window, ' ');
            wattroff(window, COLOR_PAIR(2));
        } else {
            wattron(window, COLOR_PAIR(1));
            mvwaddch(window, d.height - 1, i, ' ');
            wattroff(window, COLOR_PAIR(1));
        }
    }

    for (int i = vbarStart; i < vbarStart + vbarHeight; ++i) {
        mvwaddch(window, i, d.width - 1, ACS_CKBOARD);
    }

    std::stringstream ss;
    ss << "hbarStart: " << hbarStart;
    const std::string hbarString = ss.str();
    ss.str("");
    ss << "vbarStart: " << vbarStart;
    const std::string vbarString = ss.str();

    erase();

    move(50,50);
    printw(hbarString.c_str());
    move(51,50);
    printw(vbarString.c_str());

    refresh();
    */
    wrefresh(window);
}
