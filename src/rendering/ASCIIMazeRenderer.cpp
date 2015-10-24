#include <ncurses.h>

#include "ASCIIMazeRenderer.h"
#include "MazeCells.h"
#include "Point.h"

void ASCIIMazeRenderer::renderPos(MazeCells& cells, Point currentPosition, Point end, int x, int y) {
    move(y,x);
    if (Point(x,y) == currentPosition) {
        addch('@');
    } else if (Point(x,y) == end) {
        addch('#');
    } else if (cells.getType(x,y) == MazeCell::Type::OPEN) {
        if (cells.getProperties(x,y) == MazeCell::Properties::PART_OF_PATH) {
            addch('%');
        } else {
            addch(' ');
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
                addch('+');
                break;
            case 0b0011:
            case 0b0010:
            case 0b0001:
                addch('|');
                break;
            case 0b1100:
            case 0b1000:
            case 0b0100:
                addch('-');
                break;
            case 0b0000: //none
                addch('!'); //because it shouldn't happen
                break;
            default: //wut
                addch('?'); //because it really shouldn't happen
                break;
        }
    }
}
