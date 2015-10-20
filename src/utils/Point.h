#ifndef POINT_H
#define POINT_H

struct Point {
    int x, y;

    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

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
};

inline Point operator*(const Point& p, const int& i) {
    return Point(p.x * i, p.y * i);
}
inline Point operator*(const int& i, const Point& p) {
    return p * i;
}

#endif
