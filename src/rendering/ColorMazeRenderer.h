#ifndef COLOR_MAZE_RENDERER_H
#define COLOR_MAZE_RENDERER_H

#include <ncurses.h>

#include "maze/MazeCells.h"
#include "rendering/MazeRenderer.h"
#include "utils/Point.h"

//defined in the order they need to be supported - see constructor
#define MAZE_COLOR_BLACK   0
#define MAZE_COLOR_WHITE   1
#define MAZE_COLOR_GREEN   2
#define MAZE_COLOR_BLUE    3
#define MAZE_COLOR_RED     4
#define MAZE_COLOR_MAGENTA 5
#define NUM_MAZE_COLORS    6

#define MAZE_COLOR_CURR_POS         MAZE_COLOR_GREEN
#define MAZE_COLOR_PART_OF_PATH     MAZE_COLOR_BLUE
#define MAZE_COLOR_NOT_PART_OF_PATH MAZE_COLOR_RED
#define MAZE_COLOR_END              MAZE_COLOR_MAGENTA
#define MAZE_COLOR_EMPTY            MAZE_COLOR_BLACK
#define MAZE_COLOR_WALL             MAZE_COLOR_WHITE

//The best looking renderer
class ColorMazeRenderer : public MazeRenderer {
    public:
        ColorMazeRenderer() {
            start_color();
            int colors[] = {COLOR_BLACK, COLOR_WHITE, COLOR_GREEN,
                COLOR_BLUE, COLOR_RED, COLOR_MAGENTA};
            for (int i = 0; i < NUM_MAZE_COLORS; ++i) {
                if (i < COLOR_PAIRS)
                    init_pair(i, COLOR_BLACK, colors[i]); //i corresponds to the value
                                                          //given in the defines above
            }
        }
        void renderPos(MazeCells& cells, Point currentPosition, Point end, int x, int y);
};

#endif
