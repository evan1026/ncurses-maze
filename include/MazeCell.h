#ifndef MAZE_CELL_H
#define MAZE_CELL_H

/*************************************************************************
 * ~~~~~~~~~~~~                                                          *
 * ~ MazeCell ~                                                          *
 * ~~~~~~~~~~~~                                                          *
 *                                                                       *
 * A simple data type that holds information about each cell in the maze *
 *************************************************************************/

struct MazeCell {
    enum class Type {
        OPEN,
        WALL,
        NONE
    };
    enum class Properties {
        PART_OF_PATH,
        NOT_PART_OF_PATH,
        NONE
    };

    MazeCell::Type type;
    MazeCell::Properties properties;

    MazeCell (MazeCell::Type _t, MazeCell::Properties _p) : type(_t), properties(_p) {}
    MazeCell () : type(MazeCell::Type::NONE), properties(MazeCell::Properties::NONE) {}
};

#endif
