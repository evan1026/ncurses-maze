#ifndef MAZE_CELL_H
#define MAZE_CELL_H

struct MazeCell {
    enum Type {
        OPEN,
        WALL,
        T_NONE
    };
    enum Properties {
        PART_OF_PATH,
        NOT_PART_OF_PATH,
        P_NONE
    };

    MazeCell::Type type;
    MazeCell::Properties properties;

    MazeCell (MazeCell::Type _t, MazeCell::Properties _p) : type(_t), properties(_p) {}
    MazeCell () : type(MazeCell::Type::T_NONE), properties(MazeCell::Properties::P_NONE) {}
};

#endif
