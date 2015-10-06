#include <iostream>
#include <cctype>
#include <ncurses.h>
#include <signal.h>

#include "docopt.c"

#include "Maze.h"

void resizeHandler(int);

int main(int argc, char* argv[]) {

    /* Easy command parsing with docopt.c. Too bad it's only a WIP and can't do anything but options (-h, --version, etc.)*/
    //DocoptArgs args = docopt(argc, argv, /* help */ 1, /* version */ "0.0.1");

    //Stand-ins until docopt starts working or I become crazy/desperate enough to parse arguments myself.
    int width = 25,
        height = 25;

    try{

        /* Init ncurses window */
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        /* Init signal handler */
        signal(SIGWINCH, resizeHandler);
        Maze maze(width, height, true, 50);
        maze.render();
        move(1,1);

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

    } catch (std::exception& e) {
        endwin(); //The only reason I'm having an endwin in each section is I need to end curses before I print the exception details
        std::cout << e.what() << std::endl;
    } 


}

void resizeHandler(int sig) {
    int nh, nw;
    getmaxyx(stdscr, nh, nw);  /* get the new screen size */
    
    clear();
    refresh();
}
