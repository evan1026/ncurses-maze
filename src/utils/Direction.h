#ifndef DIRECTION_H
#define DIRECTION_H

#include "utils/Point.h"

namespace Direction {
    const Point UP    = Point( 0, -1);
    const Point DOWN  = Point( 0,  1);
    const Point LEFT  = Point(-1,  0);
    const Point RIGHT = Point( 1,  0);

    const Point directions[] = {UP, DOWN, LEFT, RIGHT};
};

#endif
