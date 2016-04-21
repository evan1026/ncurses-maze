#ifndef MAZE_GENERATOR_TYPE_H
#define MAZE_GENERATOR_TYPE_H

/**********************************************************************
 * ~~~~~~~~~~~~~~~~~~~~~                                              *
 * ~ MazeGeneratorType ~                                              *
 * ~~~~~~~~~~~~~~~~~~~~~                                              *
 *                                                                    *
 * An enumeration for keeping track of which generator is being used. *
 * TODO merge into generator class                                    *
 **********************************************************************/

enum class MazeGeneratorType {
    DFS,
    PRIMS,
    UNKNOWN
};

#endif
