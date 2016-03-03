#include <cctype>
#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <thread>

#include "ConsoleMazeRenderer.h"
#include "Game.h"
#include "Maybe.h"
#include "MazeGeneratorType.h"
#include "RenderType.h"

#define DEFAULT_DELAY 33
#define NO_DELAY 0

Game::Game(RenderType rt, int width, int height, MazeGeneratorType t) :
            maze(width, height, t), curses(), stats(Stats::getInst()), solver(maze),
            renderer(maze.width, maze.height) {

    switch (rt) {
        case RenderType::CONSOLE_RENDER_DEFAULT:
            renderer = ConsoleMazeRenderer(maze.width, maze.height);
            break;
        case RenderType::CONSOLE_RENDER_COLOR:
            renderer = ConsoleMazeRenderer(maze.width, maze.height, true);
            break;
        case RenderType::CONSOLE_RENDER_NO_COLOR:
            renderer = ConsoleMazeRenderer(maze.width, maze.height, false);
            break;
    }

    stats.setBool("win", false);
    stats.setTime("startTime", time(nullptr));
}

void Game::run() {
    int delayMS = DEFAULT_DELAY;
    bool looping = true;

    while (looping) {
        int ch = curses.getChar();

        if (solver.inProgress())
            solver.step();

        switch(ch) {
            case KEY_UP:
                countKeyPress("UP");
                maze.moveUp();
                break;
            case KEY_DOWN:
                countKeyPress("DOWN");
                maze.moveDown();
                break;
            case KEY_LEFT:
                countKeyPress("LEFT");
                maze.moveLeft();
                break;
            case KEY_RIGHT:
                countKeyPress("RIGHT");
                maze.moveRight();
                break;
            case KEY_ENTER:
            case '\n':
                countKeyPress("ENTER");
                looping = false;
                break;
            case KEY_RESIZE:
                countKeyPress("RESIZE");
                renderer.handleResize();
                break;
            case ' ':
                countKeyPress("SPACE");
                stats.setBool("cheated", true);
                if (solver.inProgress()) {
                    solver.stop();
                    delayMS = DEFAULT_DELAY;
                } else
                    solver.start();
                break;
            case 's':
                countKeyPress("s");
                if (solver.inProgress()) {
                    if (delayMS != NO_DELAY)
                        delayMS = NO_DELAY;
                    else
                        delayMS = DEFAULT_DELAY;
                }
                break;
            case 'c':
                countKeyPress("c");
                switchRenderer();
                break;
            case -1:
                //no key in queue
                break;
            default:
                if (isprint(ch)) countKeyPress(std::string(1, (char)ch));
                else             countKeyPress(std::to_string(ch));
                break;
        }

        if (maze.getCurrentPosition() == maze.end) {
            looping = false;
            stats.setBool("win", true);
        }

        renderer.render(maze);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
    }
    stats.setTime("endTime", time(nullptr));
}

void Game::countKeyPress() {
    Maybe<int> pressCount = stats.getInteger("keyPressCount");
    if (pressCount) stats.setInteger("keyPressCount", pressCount() + 1);
    else            stats.setInteger("keyPressCount", 1);
}

void Game::countKeyPress(std::string keyName) {
    std::string statsKey = "keyPressCount_" + keyName;
    Maybe<int> pressCount = stats.getInteger(statsKey);
    if (pressCount) stats.setInteger(statsKey, pressCount() + 1);
    else            stats.setInteger(statsKey, 1);

    countKeyPress();
}

void Game::switchRenderer() {
    renderer.setColor(!renderer.getColor());
    maze.refresh();
}
