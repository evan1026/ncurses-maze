#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include "MazeCells.h"

class MazeRenderer {
    public:
        virtual ~MazeRenderer() {};

        void render(MazeCells& cells, Point currentPosition, Point end);
        virtual void renderPos(MazeCells& cells, Point currentPosition, Point end, int x, int y) = 0;
};
#endif
