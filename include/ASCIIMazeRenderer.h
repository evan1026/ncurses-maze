#ifndef ASCII_MAZE_RENDERER_H
#define ASCII_MAZE_RENDERER_H

#include "MazeCells.h"
#include "MazeRenderer.h"

//For when there are no better options
class ASCIIMazeRenderer : public MazeRenderer {
    public:
        void renderPos(MazeCells& cells, Point currentPosition, Point end, int x, int y);
};

#endif
