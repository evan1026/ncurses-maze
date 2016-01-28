#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include "Maze.h"

class MazeRenderer {

protected:
    MazeRenderer() = default;

public:
    virtual ~MazeRenderer() {}
    MazeRenderer(const MazeRenderer& m) = default;
    MazeRenderer(MazeRenderer&& m) = default;
    MazeRenderer& operator=(const MazeRenderer& m) = default;
    MazeRenderer& operator=(MazeRenderer&& m) = default;

    virtual void render(Maze& maze) = 0;
    virtual void handleResize() = 0;
};
#endif
