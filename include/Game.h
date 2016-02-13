#ifndef GAME_H
#define GAME_H

#include <memory>

#include "CursesInstance.h"
#include "Maze.h"
#include "MazeGeneratorType.h"
#include "MazeRenderer.h"
#include "RenderType.h"
#include "Stats.h"

class Game {
    std::unique_ptr<MazeRenderer> renderer;
    Maze maze;
    CursesInstance curses;
    Stats& stats;

    void countKeyPress();
    void countKeyPress(std::string keyName);

public:
    Game(RenderType rt, int width, int height, MazeGeneratorType t);

    void run();

    bool win() { return stats.getBool("win")(); }
};

#endif
