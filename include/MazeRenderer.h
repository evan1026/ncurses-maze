#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include "Maze.h"

class MazeRenderer {
public:
    virtual void render(Maze& maze) = 0;
    virtual void handleResize() = 0;
    virtual ~MazeRenderer() {}
};
#endif
