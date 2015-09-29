#include <iostream>
#include <cctype>
#include <ncurses.h>
#include <signal.h>

#include "docopt.c"

#include "maze.h"

void resizeHandler(int);

int main(int argc, char* argv[]) {

    /* Easy command parsing with docopt.c. Too bad it's only a WIP and can't do anything but options (-h, --version, etc.)*/
    //DocoptArgs args = docopt(argc, argv, /* help */ 1, /* version */ "0.0.1");

    //Stand-ins until docopt starts working or I become crazy/desperate enough to parse arguments myself.
    int width = 10,
        height = 10;

    Maze maze(width, height);

    /* Init ncurses window */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    /* Init signal handler */
    signal(SIGWINCH, resizeHandler);

    /* Loop on input */
    bool looping = true;
    while (looping) {
        int ch = getch();
    
        if (ch == KEY_ENTER || ch == '\n') {
            looping = false;
        }
    }

    /* Cleanup */
    endwin();
}

void resizeHandler(int sig) {
    int nh, nw;
    getmaxyx(stdscr, nh, nw);  /* get the new screen size */
    
    clear();
    refresh();
}
