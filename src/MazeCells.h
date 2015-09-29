#ifndef MAZECELLS_H
#define MAZECELLS_H

#include "Point.h"
#include "IndexOutOfBoundsException.h"

enum MazeCell {
    OPEN,
    WALL,
    NONE
};

class MazeCells {
    MazeCell** cells;
    int width, height;

public:
    MazeCells(int w, int h) : width(w), height(h) {
        cells = new MazeCell*[width];
        for (int i = 0; i < width; ++i)
            cells[i] = new MazeCell[height];

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if (i % 2 == 1 && j % 2 == 1)
                    cells[i][j] = MazeCell::OPEN;
                else
                    cells[i][j] = MazeCell::WALL;
            }
        }
    }

    MazeCell get(int x, int y) {
        if (x < width && x >= 0 && y < height && y >= 0)
            return cells[x][y];

        return MazeCell::NONE;
    }

    void set(int x, int y) {
        if (!(x < width && x >= 0 && y < height && y >= 0))
            throw IndexOutOfBoundsException("MazeCells index invalid.");
    }
};

#endif
