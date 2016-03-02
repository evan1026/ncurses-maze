#include <ncurses.h>

#include "CursesInstance.h"

int CursesInstance::instCount = 0;
bool CursesInstance::isColor = false;

CursesInstance::CursesInstance() {
    if (instCount == 0) {
            //Init ncurses
            initscr(); //Basic init
            cbreak(); //Don't wait for \n to put chars in buffer
            noecho(); //Don't print typed characters to the screen
            keypad(stdscr, true); //Enables reading special characters like F1, F2, ..., arrow keys, etc.
            nodelay(stdscr, true); //Makes getch non-blocking
            curs_set(0); //Makes cursor invisible

            if (has_colors()) {
                isColor = true;
                start_color();
            }
    }
    instCount++;
}

CursesInstance::CursesInstance(const CursesInstance& c) {
    instCount++;
}

CursesInstance::CursesInstance(CursesInstance&& c) {
    instCount++; //Destructor of other still called, so we need this
}

CursesInstance::~CursesInstance() {
    instCount--;

    if (instCount == 0) {
        endwin();
    }
}

CursesInstance& CursesInstance::operator=(const CursesInstance& c) {
    //This one was counted in instCount and still is, so we don't
    //do anything
    return *this;
}

CursesInstance& CursesInstance::operator=(CursesInstance&& c) {
    //Once again, this one has already been counted, so we
    //don't need to count it again
    return *this;
}

bool CursesInstance::hasColor() {
    return isColor;
}

void CursesInstance::initColorPair(int pairNum, int foreground, int background) {
    init_pair(pairNum, foreground, background);
}

chtype CursesInstance::getColorPair(int pairNum) {
    return COLOR_PAIR(pairNum);
}

chtype CursesInstance::applyColorPair(int pairNum, chtype c) {
    return c | getColorPair(pairNum);
}

void CursesInstance::handleResize() {
    clear(); //rest is already handled by ncurses
}

int CursesInstance::getWidth() {
    return getmaxx(stdscr);
}

int CursesInstance::getHeight() {
    return getmaxy(stdscr);
}

int CursesInstance::getChar() {
    return getch();
}
