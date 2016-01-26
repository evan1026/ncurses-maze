#ifndef GAME_H
#define GAME_H

#include <memory>

#include "Maze.h"
#include "MazeGeneratorType.h"
#include "MazeRenderer.h"
#include "RenderType.h"

class Game {
    std::unique_ptr<MazeRenderer> renderer;
    Maze maze;
    bool won = false;

public:
    Game(RenderType rt, int width, int height, MazeGeneratorType t);
    void run();

    bool win() { return won; }
};

#endif
