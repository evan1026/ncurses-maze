#include <ncurses.h>

#include "maze/MazeCells.h"
#include "rendering/EASCIIMazeRenderer.h"
#include "utils/Point.h"

void EASCIIMazeRenderer::renderPos(MazeCells& cells, Point currentPosition, Point end, int x, int y) {
    move(y,x);
    if (Point(x,y) == currentPosition) {
        addch('@');
    } else if (Point(x,y) == end) {
        addch(ACS_CKBOARD);
    } else if (cells.getType(x,y) == MazeCell::Type::OPEN) {
        if (cells.getProperties(x,y) == MazeCell::Properties::PART_OF_PATH) {
            addch('#');
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
            case 0b1111: //up & down & left & right
                addch(ACS_PLUS);
                break;
            case 0b1110: //down & left & right
                addch(ACS_TTEE);
                break;
            case 0b1101: //up & left & right
                addch(ACS_BTEE);
                break;
            case 0b1011: //up & down & right
                addch(ACS_LTEE);
                break;
            case 0b0111: //up & down & left
                addch(ACS_RTEE);
                break;
            case 0b1100: //left & right
                addch(ACS_HLINE);
                break;
            case 0b1010: //right & down
                addch(ACS_ULCORNER);
                break;
            case 0b1001: //right & up
                addch(ACS_LLCORNER);
                break;
            case 0b0110: //down & left
                addch(ACS_URCORNER);
                break;
            case 0b0101: //up & left
                addch(ACS_LRCORNER);
                break;
            case 0b0011: //up & down
                addch(ACS_VLINE);
                break;
            case 0b1000: //right
                addch(ACS_HLINE);
                break;
            case 0b0100: //left
                addch(ACS_HLINE);
                break;
            case 0b0010: //down
                addch(ACS_VLINE);
                break;
            case 0b0001: //up
                addch(ACS_VLINE);
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
