#ifndef CURSES_INSTANCE_H
#define CURSES_INSTANCE_H

#include <ncurses.h>

/**************************************************************************
 * ~~~~~~~~~~~~~~~~~~                                                     *
 * ~ CursesInstance ~                                                     *
 * ~~~~~~~~~~~~~~~~~~                                                     *
 *                                                                        *
 * Serves as a wrapper for the primitive C functions provided by ncurses. *
 * This class counts the number of references there are to it, so that    *
 * it can start and end the ncurses session at the correct times. Most    *
 * of these functions simply forward to the underlying C functions.       *
 *                                                                        *
 * Full docs on each function can be found in the corresponding cpp file. *
 **************************************************************************/

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
