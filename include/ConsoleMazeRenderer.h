#ifndef CONSOLE_MAZE_RENDERER_H
#define CONSOLE_MAZE_RENDERER_H

#include "ConsoleViewport.h"
#include "CursesInstance.h"
#include "Maze.h"

/**************************************************************************
 * ~~~~~~~~~~~~~~~~~~~~~~~                                                *
 * ~ ConsoleMazeRenderer ~                                                *
 * ~~~~~~~~~~~~~~~~~~~~~~~                                                *
 *                                                                        *
 * This class is responsible for rendering the maze to the console.       *
 * It serves as the link between the Maze class and the CursesInstance.   *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

class ConsoleMazeRenderer {
    ConsoleViewport mazeWindow;
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

    bool getColor();
    void setColor(bool c);


    /**************************************************************************
     * ~~~~~~~~~~~~~~                                                         *
     * ~ RenderType ~                                                         *
     * ~~~~~~~~~~~~~~                                                         *
     *                                                                        *
     * An enumeration that keeps track of the type of render (i.e. whether or *
     * not to use colors).                                                    *
     **************************************************************************/

    enum class RenderType {
        COLOR,
        NO_COLOR,
        DEFAULT
    };
};

#endif
