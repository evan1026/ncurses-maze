#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include "MazeCells.h"

class MazeRenderer {
    public:
        void render(WINDOW* win, MazeCells& cells, Point currentPosition, Point end);
        virtual void renderPos(WINDOW* win, MazeCells& cells, Point currentPosition, Point end, int x, int y) = 0;
};
#endif
