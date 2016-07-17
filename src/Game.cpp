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
#include "MazeGenerator.h"
#include "RenderType.h"

#define DEFAULT_DELAY 33
#define NO_DELAY 0

Game::Game(RenderType rt, int width, int height, MazeGenerator::Type t) :
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

    stats.set<bool>("win", false);
    stats.set<time_t>("startTime", time(nullptr));
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
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                move(ch);
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
                stats.set<bool>("cheated", true);
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
            stats.set<bool>("win", true);
        }

        renderer.render(maze);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
    }
    stats.set<time_t>("endTime", time(nullptr));
}

void Game::countKeyPress() {
    stats.incrementOrCreateInt("keyPressCount");
}

void Game::countKeyPress(std::string keyName) {
    std::string statsKey = "keyPressCount_" + keyName;
    stats.incrementOrCreateInt(statsKey);

    countKeyPress();
}

void Game::switchRenderer() {
    renderer.setColor(!renderer.getColor());
    maze.refresh();
}

void Game::move(int direction) {
    bool res;

    if (direction == KEY_UP) {
        countKeyPress("UP");
        res = maze.moveUp();
    } else if (direction == KEY_DOWN) {
        countKeyPress("DOWN");
        res = maze.moveDown();
    } else if (direction == KEY_LEFT) {
        countKeyPress("LEFT");
        res = maze.moveLeft();
    } else if (direction == KEY_RIGHT) {
        countKeyPress("RIGHT");
        res = maze.moveRight();
    } else {
        std::cerr << "Error in game.cpp - Game::Move - Invalid argument." << std::endl;
        return;
    }

    if (res) {
        stats.incrementOrCreateInt("spacesMoved");
    } else {
        stats.incrementOrCreateInt("blockedMoves");
    }
}
