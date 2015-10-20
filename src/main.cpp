#include <cctype>
#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>

//#include "docopt.c"

#include "maze/Maze.h"

void resizeHandler(int);
Maze* theMaze;

int main(int argc, char* argv[]) {

    /* Easy command parsing with docopt.c. Too bad it's only a WIP and can't do anything but options (-h, --version, etc.)*/
    //DocoptArgs args = docopt(argc, argv, /* help */ 1, /* version */ "0.0.1");

    //Stand-ins until docopt starts working or I become crazy/desperate enough to parse arguments myself.
    //int width = 78,
    //    height = 26;

    try{

        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        //if (2 * width + 1 > w.ws_col || 2 * height + 1 > w.ws_row) {
        //    std::cout << "Terminal not large enough for specified size" << std::endl;
        //    return 1;
        //}

        /* Init ncurses window */
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);

        /* Init signal handler */
        signal(SIGWINCH, resizeHandler);

        /* Maze cursor invisible */
        curs_set(0);

        /* Init maze */
        //Maze maze((w.ws_col - 1) / 2, (w.ws_row - 1) / 2, false, 25);
        Maze maze(30, 15, false);
        theMaze = &maze;
        maze.render();

        /* Loop on input */
        bool looping = true;
        while (looping) {
            int ch = getch();

            switch (ch) {
                case KEY_UP:
                    maze.tryMoveUp();
                    break;
                case KEY_DOWN:
                    maze.tryMoveDown();
                    break;
                case KEY_LEFT:
                    maze.tryMoveLeft();
                    break;
                case KEY_RIGHT:
                    maze.tryMoveRight();
                    break;
                default:
                    maze.render();
                    break;
            }

            if (ch == KEY_ENTER || ch == '\n' || maze.win()) {
                looping = false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(33)); //33 ms ~ 30 fps
        }
        
        /* Cleanup */
        endwin();
        if (maze.win()) std::cout << "YOU WIN" << std::endl;

    } catch (std::exception& e) {
        endwin(); //The only reason I'm having an endwin in each section is I need to end curses before I print the exception details
        std::cout << e.what() << std::endl;
    } 


}

void resizeHandler(int sig) {
    endwin();
    theMaze->render();
}
