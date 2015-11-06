#include <ncurses.h>

#include "ColorMazeRenderer.h"
#include "MazeCells.h"
#include "Point.h"

void MazeRenderer::render(WINDOW* win, MazeCells& cells, Point currentPosition, Point end) {

    werase(win);

    Point cursorPos;
    getyx(win, cursorPos.y, cursorPos.x);

    Point screenDim;
    getmaxyx(win, screenDim.y, screenDim.x);

    for (int y = 0; y < cells.getHeight() && y < screenDim.y; ++y) {
        for (int x = 0; x < cells.getWidth() && x < screenDim.x; ++x) {
            renderPos(win, cells, currentPosition, end, x, y);
        }
    }

    wmove(win, cursorPos.y, cursorPos.x);

    //Removed since we're now drawing to an internal buffer window, rather than the actual window on screen
    //wrefresh(win);
}
