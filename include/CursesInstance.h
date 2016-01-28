#ifndef CURSES_INSTANCE_H
#define CURSES_INSTANCE_H

#include <ncurses.h>

class CursesInstance {
    static int instCount;
    static bool isColor;

public:
    CursesInstance();
    CursesInstance(const CursesInstance& c);
    CursesInstance(CursesInstance&& c);
    ~CursesInstance();
    CursesInstance& operator=(const CursesInstance& c);
    CursesInstance& operator=(CursesInstance&& c);

    bool hasColor();

    void initColorPair(int pairNum, int foreground, int background);
    chtype getColorPair(int pairNum);
    chtype applyColorPair(int pairNum, chtype c);

    void handleResize();

    int getWidth();
    int getHeight();

    int getChar();
};

#endif
