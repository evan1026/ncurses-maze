#ifndef CONSOLE_MAZE_RENDERER_H
#define CONSOLE_MAZE_RENDERER_H

#include "ConsoleViewport.h"
#include "CursesInstance.h"
#include "Maze.h"
#include "MazeRenderer.h"

class ConsoleMazeRenderer : public MazeRenderer {
    ConsoleViewport window;
    CursesInstance curses;

    void renderCell(Maze& maze, int x, int y);
    chtype getASCIIFromFlags(unsigned char flags);
    Dimension getWindowDimension();

public:
    ConsoleMazeRenderer(int mazeWidth, int mazeHeight);
    void render(Maze& maze);
    void handleResize();
};

#endif
