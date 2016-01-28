#ifndef CONSOLE_MAZE_RENDERER_H
#define CONSOLE_MAZE_RENDERER_H

#include "ConsoleViewport.h"
#include "CursesInstance.h"
#include "Maze.h"
#include "MazeRenderer.h"

class ConsoleMazeRenderer : public MazeRenderer {
    ConsoleViewport window;
    CursesInstance curses;
    bool color;

    void renderCell(Maze& maze, int x, int y);
    chtype getASCIIFromFlags(unsigned char flags);
    Dimension getWindowDimension();
    void initColors();

public:
    ConsoleMazeRenderer(int mazeWidth, int mazeHeight);
    ConsoleMazeRenderer(int mazeWidth, int mazeHeight, bool color);

    void render(Maze& maze);
    void handleResize();
};

#endif
