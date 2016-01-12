#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "ConsoleMazeRenderer.h"
#include "Game.h"
#include "MazeRenderer.h"
#include "RenderType.h"

Game::Game(RenderType rt, int width, int height) : maze(width, height) {
    if (rt == RenderType::ConsoleRender) {
        renderer = std::unique_ptr<MazeRenderer>(new ConsoleMazeRenderer(maze.width, maze.height));
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

        switch(ch) {
            case KEY_UP:
                maze.moveUp();
                break;
            case KEY_DOWN:
                maze.moveDown();
                break;
            case KEY_LEFT:
                maze.moveLeft();
                break;
            case KEY_RIGHT:
                maze.moveRight();
                break;
            case KEY_ENTER:
            case '\n':
                looping = false;
                break;
            case KEY_RESIZE:
                renderer->handleResize();
                break;
            default:
                break;
        }

        if (maze.getCurrentPosition() == maze.end) {
            looping = false;
            won = true;
        }

        renderer->render(maze);
        std::this_thread::sleep_for(std::chrono::milliseconds(33)); //33 ms ~ 30 fps
    }
}
