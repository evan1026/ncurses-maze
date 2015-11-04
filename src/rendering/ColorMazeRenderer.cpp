#include <ncurses.h>

#include "ColorMazeRenderer.h"
#include "MazeCells.h"
#include "Point.h"

const ColorMazeRenderer* ColorMazeRenderer::instance = new ColorMazeRenderer();
bool ColorMazeRenderer::cursesInitState = false;

void ColorMazeRenderer::renderPos(WINDOW* win, MazeCells& cells, Point currentPosition, Point end, int x, int y) const {
     //Default is -1 because I want it to crash while in development
     //We should never get there, so I want to know if we do
     int colorIndex = -1;

     initCursesIfNotAlready();

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

     wmove(win, y, x);
     wattron(win, COLOR_PAIR(colorIndex));
     waddch(win, ' ');
     wattroff(win, COLOR_PAIR(colorIndex));
}
