#ifndef GAME_H
#define GAME_H

#include <memory>

#include "ConsoleMazeRenderer.h"
#include "CursesInstance.h"
#include "Maze.h"
#include "MazeGeneratorType.h"
#include "RenderType.h"
#include "Stats.h"

class Game {
    Maze maze;
    CursesInstance curses;
    Stats& stats;
    Maze::Solver solver;
    ConsoleMazeRenderer renderer;

    void countKeyPress();
    void countKeyPress(std::string keyName);
    void switchRenderer();
    void move(int direction);

public:
    Game(RenderType rt, int width, int height, MazeGeneratorType t);

    void run();

    bool win() { return stats.get<bool>("win")(); }
};

#endif
