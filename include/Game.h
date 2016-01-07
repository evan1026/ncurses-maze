#ifndef GAME_H
#define GAME_H

#include <memory>

#include "Maze.h"
#include "MazeRenderer.h"
#include "RenderType.h"

class Game {
    std::unique_ptr<MazeRenderer> renderer;
    Maze maze;
    bool won = false;

public:
    Game(RenderType rt, int width, int height);
    void run();

    bool win() { return won; }
};

#endif
