#include <ncurses.h>

#include "maze/MazeCells.h"
#include "rendering/ColorMazeRenderer.h"
#include "utils/Point.h"

void ColorMazeRenderer::renderPos(MazeCells& cells, Point currentPosition, Point end, int x, int y) {
     //Default is -1 because I want it to crash while in development
     //We should never get there, so I want to know if we do
     int colorIndex = -1;

     if (cells.getType(x,y) == MazeCell::Type::OPEN) {
         if (Point(x,y) == currentPosition) {
             colorIndex = MAZE_COLOR_CURR_POS;
         } else if (cells.getProperties(x,y) == MazeCell::Properties::PART_OF_PATH) {
             colorIndex = MAZE_COLOR_PART_OF_PATH;
         } else if (cells.getProperties(x,y) == MazeCell::Properties::NOT_PART_OF_PATH) {
             colorIndex = MAZE_COLOR_NOT_PART_OF_PATH;
         } else if (Point(x,y) == end) {
             colorIndex = MAZE_COLOR_END;
         } else {
             colorIndex = MAZE_COLOR_EMPTY;
         }
     } else {
         colorIndex = MAZE_COLOR_WALL;
     }

     move(y,x);
     attron(COLOR_PAIR(colorIndex));
     addch(' ');
     attroff(COLOR_PAIR(colorIndex));
}
