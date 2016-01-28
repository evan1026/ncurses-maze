#include <chrono>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <thread>

#include "ConsoleMazeRenderer.h"
#include "Game.h"
#include "MazeGeneratorType.h"
#include "MazeRenderer.h"
#include "RenderType.h"

Game::Game(RenderType rt, int width, int height, MazeGeneratorType t) : maze(width, height, t), curses() {
    switch (rt) {
        case RenderType::CONSOLE_RENDER_DEFAULT:
            renderer = std::unique_ptr<MazeRenderer>(new ConsoleMazeRenderer(maze.width, maze.height));
            break;
        case RenderType::CONSOLE_RENDER_COLOR:
            renderer = std::unique_ptr<MazeRenderer>(new ConsoleMazeRenderer(maze.width, maze.height, true));
            break;
        case RenderType::CONSOLE_RENDER_NO_COLOR:
            renderer = std::unique_ptr<MazeRenderer>(new ConsoleMazeRenderer(maze.width, maze.height, false));
            break;
        default:
            std::cerr << "RenderType not recognized in Game.cpp line " << __LINE__ << std::endl;
            renderer = std::unique_ptr<MazeRenderer>(nullptr); //Not ideal, but we shouldn't be here anyway
            break;
    }
}

void Game::run() {
    bool looping = true;
    while (looping) {
        int ch = curses.getChar();

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
