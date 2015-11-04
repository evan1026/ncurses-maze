#include <ncurses.h>

#include "EASCIIMazeRenderer.h"
#include "MazeCells.h"
#include "Point.h"

const EASCIIMazeRenderer* EASCIIMazeRenderer::instance = new EASCIIMazeRenderer();

void EASCIIMazeRenderer::renderPos(WINDOW* win, MazeCells& cells, Point currentPosition, Point end, int x, int y) const {
    wmove(win, y, x);
    if (Point(x,y) == currentPosition) {
        waddch(win, '@');
    } else if (Point(x,y) == end) {
        waddch(win, ACS_CKBOARD);
    } else if (cells.getType(x,y) == MazeCell::Type::OPEN) {
        if (cells.getProperties(x,y) == MazeCell::Properties::PART_OF_PATH) {
            waddch(win, '#');
        } else {
            waddch(win, ' ');
        }
    } else {
        MazeCell::Type up    = cells.upperNeighbor(x,y).type,
                       down  = cells.lowerNeighbor(x,y).type,
                       left  = cells.leftNeighbor(x,y).type,
                       right = cells.rightNeighbor(x,y).type;

        short flags = 0;
        if (up    == MazeCell::Type::WALL) flags |= 0b0001;
        if (down  == MazeCell::Type::WALL) flags |= 0b0010;
        if (left  == MazeCell::Type::WALL) flags |= 0b0100;
        if (right == MazeCell::Type::WALL) flags |= 0b1000;

        switch (flags) {
            case 0b1111: //up & down & left & right
                waddch(win, ACS_PLUS);
                break;
            case 0b1110: //down & left & right
                waddch(win, ACS_TTEE);
                break;
            case 0b1101: //up & left & right
                waddch(win, ACS_BTEE);
                break;
            case 0b1011: //up & down & right
                waddch(win, ACS_LTEE);
                break;
            case 0b0111: //up & down & left
                waddch(win, ACS_RTEE);
                break;
            case 0b1100: //left & right
                waddch(win, ACS_HLINE);
                break;
            case 0b1010: //right & down
                waddch(win, ACS_ULCORNER);
                break;
            case 0b1001: //right & up
                waddch(win, ACS_LLCORNER);
                break;
            case 0b0110: //down & left
                waddch(win, ACS_URCORNER);
                break;
            case 0b0101: //up & left
                waddch(win, ACS_LRCORNER);
                break;
            case 0b0011: //up & down
                waddch(win, ACS_VLINE);
                break;
            case 0b1000: //right
                waddch(win, ACS_HLINE);
                break;
            case 0b0100: //left
                waddch(win, ACS_HLINE);
                break;
            case 0b0010: //down
                waddch(win, ACS_VLINE);
                break;
            case 0b0001: //up
                waddch(win, ACS_VLINE);
                break;
            case 0b0000: //none
                waddch(win, '!'); //because it shouldn't happen
                break;
            default: //wut
                waddch(win, '?'); //because it really shouldn't happen
                break;
        }
    }
}
