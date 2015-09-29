#include <iostream>
#include <cctype>
#include <ncurses.h>
#include <signal.h>

void resizeHandler(int);

int main() {

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
        } else if (isascii(ch) && isprint(ch)) {
            echochar(ch);
        } else {
            printw("(%d)", ch);
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
