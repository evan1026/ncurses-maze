#include <chrono>
#include <iostream>
#include <memory>
#include <sys/ioctl.h>
#include <thread>
#include <unistd.h>

#include "ConsoleMazeRenderer.h"
#include "Game.h"
#include "MazeRenderer.h"
#include "RenderType.h"

Game::Game(RenderType rt, int width, int height) : maze(width, height) {
    if (rt == RenderType::ConsoleRender) {

        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        /*int result = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);   //Allows for explaination of errors, but that requires
        if (result < 0) {                                      //More libraries, so I'm leaving it out unless needed
            fprintf(stderr, "%s\n", explain_ioctl(STDOUT_FILENO, TIOCGWINSZ, &w));
            exit(1);
        }*/

        renderer = std::unique_ptr<MazeRenderer>(new ConsoleMazeRenderer(w.ws_col, w.ws_row, maze.width, maze.height));
    } else {
        std::cerr << "RenderType not recognized in Game.cpp line " << __LINE__ << std::endl;
        renderer = std::unique_ptr<MazeRenderer>(nullptr); //Not ideal, but we shouldn't be here anyway
    }
}

void Game::run() {

    //TODO Input based on input type
    bool looping = true;
    while (looping) {
        int ch = getch();

        if (ch == KEY_ENTER || ch == '\n') {
            looping = false;
        }

        renderer->render(maze);
        std::this_thread::sleep_for(std::chrono::milliseconds(33)); //33 ms ~ 30 fps
    }
}
