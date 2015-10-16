#include <ncurses.h>

#include "ColorMazeRenderer.h"
#include "MazeCells.h"
#include "Point.h"

void MazeRenderer::render(MazeCells& cells, Point currentPosition, Point end) {
    erase();
    Point cursorPos;
    getyx(stdscr, cursorPos.y, cursorPos.x);
    for (int y = 0; y < cells.getHeight(); ++y) {
        for (int x = 0; x < cells.getWidth(); ++x) {
            renderPos(cells, currentPosition, end, x, y);
        }
    }
    move(cursorPos.y, cursorPos.x);
    refresh();
}
