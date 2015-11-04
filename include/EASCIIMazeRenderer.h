#ifndef EASCII_MAZE_RENDERER_H
#define EASCII_MAZE_RENDERER_H

#include <ncurses.h>

#include "MazeCells.h"
#include "MazeRenderer.h"
#include "Point.h"

//For when color is not an option, but you still want it to look kinda good
class EASCIIMazeRenderer : public MazeRenderer {
    EASCIIMazeRenderer() {}
    static const EASCIIMazeRenderer* instance;
    public:
        void renderPos(WINDOW* win, MazeCells& cells, Point currentPosition, Point end, int x, int y) const;
        static const EASCIIMazeRenderer* getInstance() {
            return instance;
        }
};

#endif
