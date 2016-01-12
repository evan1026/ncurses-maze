#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "ConsoleMazeRenderer.h"
#include "ConsoleViewport.h"
#include "Dimension.h"
#include "Maze.h"

#define MAZE_COLOR_EMPTY     0
#define MAZE_COLOR_WALL      1
#define MAZE_COLOR_PATH      2
#define MAZE_COLOR_NOT_PATH  3
#define MAZE_COLOR_END       4
#define MAZE_COLOR_CURRENT   5

ConsoleMazeRenderer::ConsoleMazeRenderer(int _mazeWidth, int _mazeHeight) :
                window(getWindowDimension(), _mazeWidth, _mazeHeight) {

    //Init ncurses
    initscr(); //Basic init
    cbreak(); //Don't wait for \n to put chars in buffer
    noecho(); //Don't print typed characters to the screen
    keypad(stdscr, TRUE); //Enables reading special characters like F1, F2, ..., arrow keys, etc.
    nodelay(stdscr, TRUE); //Makes getch non-blocking
    curs_set(0); //Makes cursor invisible

    if (has_colors()) {
        color = true;
        start_color();

        init_pair(MAZE_COLOR_EMPTY,    COLOR_BLACK, COLOR_BLACK);
        init_pair(MAZE_COLOR_WALL,     COLOR_BLACK, COLOR_WHITE);
        init_pair(MAZE_COLOR_PATH,     COLOR_BLACK, COLOR_BLUE);
        init_pair(MAZE_COLOR_NOT_PATH, COLOR_BLACK, COLOR_RED);
        init_pair(MAZE_COLOR_END,      COLOR_BLACK, COLOR_MAGENTA);
        init_pair(MAZE_COLOR_CURRENT,  COLOR_BLACK, COLOR_GREEN);
    }

    window.init();
}

Dimension ConsoleMazeRenderer::getWindowDimension() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return Dimension(0, 0, w.ws_col, w.ws_row);
}

ConsoleMazeRenderer::~ConsoleMazeRenderer() {
    endwin(); //ncurses cleanup
}

void ConsoleMazeRenderer::handleResize() {
    clear();

    int width,
        height;

    getmaxyx(stdscr, height, width);
    window.resize(Dimension(0, 0, width, height));
}

void ConsoleMazeRenderer::render(Maze& maze) {
    window.centerOn(maze.getCurrentPosition());
    for (int i = 0; i < maze.width; ++i) {
        for (int j = 0; j < maze.height; ++j) {
            renderCell(maze, i, j);
        }
    }
    window.refresh();
}

void ConsoleMazeRenderer::renderCell(Maze& maze, int x, int y) {
    MazeCell cell = maze.get(x, y);
    chtype value = '['; //All random chars like this are to ease debugging

    if (color) {
        value = ' ';

        if (maze.getCurrentPosition() == Point(x,y)) {
            value = value | COLOR_PAIR(MAZE_COLOR_CURRENT);
        } else if (maze.end == Point(x,y)) {
            value = value | COLOR_PAIR(MAZE_COLOR_END);
        } else {
            if (cell.type == MazeCell::Type::OPEN) {
                if (cell.properties == MazeCell::Properties::PART_OF_PATH) {
                    value = value | COLOR_PAIR(MAZE_COLOR_PATH);
                } else if (cell.properties == MazeCell::Properties::NOT_PART_OF_PATH) {
                    value = value | COLOR_PAIR(MAZE_COLOR_NOT_PATH);
                } else {
                    value = value | COLOR_PAIR(MAZE_COLOR_EMPTY);
                }
            } else if (cell.type == MazeCell::Type::WALL) {
                value = value | COLOR_PAIR(MAZE_COLOR_WALL);
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

    window.set(x, y, value);
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
