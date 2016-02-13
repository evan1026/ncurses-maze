#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "ConsoleMazeRenderer.h"
#include "ConsoleViewport.h"
#include "CursesInstance.h"
#include "Dimension.h"
#include "Maze.h"

#define MAZE_COLOR_EMPTY     0
#define MAZE_COLOR_WALL      1
#define MAZE_COLOR_PATH      2
#define MAZE_COLOR_NOT_PATH  3
#define MAZE_COLOR_END       4
#define MAZE_COLOR_CURRENT   5

ConsoleMazeRenderer::ConsoleMazeRenderer(int mazeWidth, int mazeHeight) :
                mazeWindow(getWindowDimension(), mazeWidth, mazeHeight), curses(), color(curses.hasColor()) {
    if (color) {
        initColors();
    }
}

ConsoleMazeRenderer::ConsoleMazeRenderer(int mazeWidth, int mazeHeight, bool _color) :
                ConsoleMazeRenderer(mazeWidth, mazeHeight) {
    color = _color;
}

void ConsoleMazeRenderer::initColors() {
    curses.initColorPair(MAZE_COLOR_EMPTY,    COLOR_BLACK, COLOR_BLACK);
    curses.initColorPair(MAZE_COLOR_WALL,     COLOR_BLACK, COLOR_WHITE);
    curses.initColorPair(MAZE_COLOR_PATH,     COLOR_BLACK, COLOR_BLUE);
    curses.initColorPair(MAZE_COLOR_NOT_PATH, COLOR_BLACK, COLOR_RED);
    curses.initColorPair(MAZE_COLOR_END,      COLOR_BLACK, COLOR_MAGENTA);
    curses.initColorPair(MAZE_COLOR_CURRENT,  COLOR_BLACK, COLOR_GREEN);
}

Dimension ConsoleMazeRenderer::getWindowDimension() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return Dimension(0, 0, w.ws_col, w.ws_row);
}

void ConsoleMazeRenderer::handleResize() {
    curses.handleResize();

    int width = curses.getWidth();
    int height = curses.getHeight();
    mazeWindow.resize(Dimension(0, 0, width, height));
}

void ConsoleMazeRenderer::render(Maze& maze) {
    mazeWindow.centerOn(maze.getCurrentPosition());
    for (int i = 0; i < maze.width; ++i) {
        for (int j = 0; j < maze.height; ++j) {
            renderCell(maze, i, j);
        }
    }
    mazeWindow.refresh();
}

void ConsoleMazeRenderer::renderCell(Maze& maze, int x, int y) {
    MazeCell cell = maze.get(x, y);
    chtype value = '['; //All random chars like this are to ease debugging

    if (color) {
        value = ' ';

        if (maze.getCurrentPosition() == Point(x,y)) {
            value = curses.applyColorPair(MAZE_COLOR_CURRENT, value);
        } else if (maze.end == Point(x,y)) {
            value = curses.applyColorPair(MAZE_COLOR_END, value);
        } else {
            if (cell.type == MazeCell::Type::OPEN) {
                if (cell.properties == MazeCell::Properties::PART_OF_PATH) {
                    value = curses.applyColorPair(MAZE_COLOR_PATH, value);
                } else if (cell.properties == MazeCell::Properties::NOT_PART_OF_PATH) {
                    value = curses.applyColorPair(MAZE_COLOR_NOT_PATH, value);
                } else {
                    value = curses.applyColorPair(MAZE_COLOR_EMPTY, value);
                }
            } else if (cell.type == MazeCell::Type::WALL) {
                value = curses.applyColorPair(MAZE_COLOR_WALL, value);
            } else {
                value = '?';
            }
        }
    } else {
        if (maze.getCurrentPosition() == Point(x,y)) {
            value = '@';
        } else if (maze.end == Point(x,y)) {
            value = ACS_CKBOARD;
        } else {
            if (cell.type == MazeCell::Type::OPEN) {
                if (cell.properties == MazeCell::Properties::PART_OF_PATH) {
                    value = '#';
                } else if (cell.properties == MazeCell::Properties::NOT_PART_OF_PATH) {
                    value = '~';
                } else {
                    value = ' ';
                }
            } else if (cell.type == MazeCell::Type::WALL) {
                MazeCell::Type up    = maze.getUpperNeighbor(x, y).type,
                               down  = maze.getLowerNeighbor(x, y).type,
                               left  = maze.getLeftNeighbor (x, y).type,
                               right = maze.getRightNeighbor(x, y).type;

                unsigned char flags = 0;
                if (up    == MazeCell::Type::WALL) flags |= 0b0001;
                if (down  == MazeCell::Type::WALL) flags |= 0b0010;
                if (left  == MazeCell::Type::WALL) flags |= 0b0100;
                if (right == MazeCell::Type::WALL) flags |= 0b1000;

                value = getASCIIFromFlags(flags);
            } else {
                value = '?';
            }
        }
    }

    mazeWindow.set(x, y, value);
}

chtype ConsoleMazeRenderer::getASCIIFromFlags(unsigned char flags) {
    switch (flags) {
        case 0b1111: //up & down & left & right
            return ACS_PLUS;
        case 0b1110: //down & left & right
            return ACS_TTEE;
        case 0b1101: //up & left & right
            return ACS_BTEE;
        case 0b1011: //up & down & right
            return ACS_LTEE;
        case 0b0111: //up & down & left
            return ACS_RTEE;
        case 0b1100: //left & right
            return ACS_HLINE;
        case 0b1010: //right & down
            return ACS_ULCORNER;
        case 0b1001: //right & up
            return ACS_LLCORNER;
        case 0b0110: //down & left
            return ACS_URCORNER;
        case 0b0101: //up & left
            return ACS_LRCORNER;
        case 0b0011: //up & down
            return ACS_VLINE;
        case 0b1000: //right
            return ACS_HLINE;
        case 0b0100: //left
            return ACS_HLINE;
        case 0b0010: //down
            return ACS_VLINE;
        case 0b0001: //up
            return ACS_VLINE;
        case 0b0000: //none
            return '{'; //because it shouldn't happen
        default: //wut
            return '}'; //because it really shouldn't happen
    }
}
