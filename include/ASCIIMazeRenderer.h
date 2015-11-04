#ifndef ASCII_MAZE_RENDERER_H
#define ASCII_MAZE_RENDERER_H

#include <ncurses.h>

#include "MazeCells.h"
#include "MazeRenderer.h"

//For when there are no better options
class ASCIIMazeRenderer : public MazeRenderer {
    ASCIIMazeRenderer() {}
    static const ASCIIMazeRenderer* instance;
    public:
        void renderPos(WINDOW* win, MazeCells& cells, Point currentPosition, Point end, int x, int y) const;
        static const ASCIIMazeRenderer* getInstance() {
            return instance;
        }
};

#endif
