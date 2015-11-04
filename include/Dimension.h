#ifndef DIMENSION_H
#define DIMENSION_H

struct Dimension {
    int x, y, width, height;
    Dimension(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {};
    Dimension() : x(0), y(0), width(0), height(0) {}
};

#endif
