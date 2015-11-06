#include <ncurses.h>

#include "ASCIIMazeRenderer.h"
#include "MazeCells.h"
#include "Point.h"

ASCIIMazeRenderer* ASCIIMazeRenderer::instance = new ASCIIMazeRenderer();

void ASCIIMazeRenderer::renderPos(WINDOW* win, MazeCells& cells, Point currentPosition, Point end, int x, int y) {
    wmove(win, y,x);
    if (Point(x,y) == currentPosition) {
        waddch(win, '@');
    } else if (Point(x,y) == end) {
        waddch(win, '#');
    } else if (cells.getType(x,y) == MazeCell::Type::OPEN) {
        if (cells.getProperties(x,y) == MazeCell::Properties::PART_OF_PATH) {
            waddch(win, '%');
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
            case 0b1111:
            case 0b1110:
            case 0b1101:
            case 0b1011:
            case 0b0111:
            case 0b1010:
            case 0b1001:
            case 0b0110:
            case 0b0101:
                waddch(win, '+');
                break;
            case 0b0011:
            case 0b0010:
            case 0b0001:
                waddch(win, '|');
                break;
            case 0b1100:
            case 0b1000:
            case 0b0100:
                waddch(win, '-');
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
