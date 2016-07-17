#ifndef GAME_H
#define GAME_H

#include "ConsoleMazeRenderer.h"
#include "CursesInstance.h"
#include "Maze.h"
#include "MazeGenerator.h"
#include "RenderType.h"
#include "Stats.h"

/**************************************************************************
 * ~~~~~~~~                                                               *
 * ~ Game ~                                                               *
 * ~~~~~~~~                                                               *
 *                                                                        *
 * A class that represents the entire game as a whole. This initializes   *
 * the components and links them up as needed, as well as runs the main   *
 * loop which handles dispatching input and output.                       *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

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
    Game(RenderType rt, int width, int height, MazeGenerator::Type t);

    void run();

    bool win() { return stats.get<bool>("win")(); }
};

#endif
