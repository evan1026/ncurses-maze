#ifndef POINT_H
#define POINT_H

/**************************************************************************
 * ~~~~~~~~~                                                              *
 * ~ Point ~                                                              *
 * ~~~~~~~~~                                                              *
 *                                                                        *
 * Represents a point on the maze or an offset, depending on how it's     *
 * being used. This file also defines a number of operators for comparing *
 * and manipulating points.                                               *
 **************************************************************************/

struct Point {
    int x,
        y;

    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point(const Point& p) : x(p.x), y(p.y) {}

    inline bool operator==(const Point& p) const {
        return p.x == x && p.y == y;
    }
    inline bool operator!=(const Point& p) const {
        return !(p == *this);
    }
    inline Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }
    inline Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
    inline Point operator*(const int& i) const {
        return Point(x * i, y * i);
    }
    inline Point operator/(const int& i) const {
        return Point(x / i, y / i);
    }
    inline Point& operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
    inline Point& operator+=(const Point& p) {
        return ((*this) = (*this) + p);
    }
    inline Point& operator-=(const Point& p) {
        return ((*this) = (*this) - p);
    }
    inline Point& operator*=(const int& i) {
        return ((*this) = (*this) * i);
    }
    inline Point& operator/=(const int& i) {
        return ((*this) = (*this) / i);
    }
};

inline Point operator*(const int& i, const Point& p) {
    return p * i;
}

#endif
