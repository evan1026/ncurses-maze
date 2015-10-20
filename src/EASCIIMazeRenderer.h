#ifndef EASCII_MAZE_RENDERER_H
#define EASCII_MAZE_RENDERER_H

#include "MazeRenderer.h"
#include "MazeCells.h"
#include "Point.h"

//For when color is not an option, but you still want it to look kinda good
class EASCIIMazeRenderer : public MazeRenderer {
    public:
        void renderPos(MazeCells& cells, Point currentPosition, Point end, int x, int y);
};

#endif
