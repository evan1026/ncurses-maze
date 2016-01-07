#include <ncurses.h>

#include "ConsoleWindow.h"
#include "Point.h"

ConsoleWindow::ConsoleWindow(int _x, int _y, int _width, int _height) : width(_width), height(_height), x(_x), y(_y) {}

ConsoleWindow::~ConsoleWindow() {
    if (window != NULL) delwin(window);
}

void ConsoleWindow::set(int x, int y, chtype c) {
    if (window != NULL) mvwaddch(window, y, x, c);
}

void ConsoleWindow::set(Point p, chtype c) {
    set(p.x, p.y, c);
}

chtype ConsoleWindow::get(int x, int y) {
    if (window != NULL) return mvwgetch(window, y, x);
    return 0;
}

chtype ConsoleWindow::get(Point p) {
    return get(p.x, p.y);
}

void ConsoleWindow::drawBox() {
    if (window != NULL) box(window, 0, 0);
}

void ConsoleWindow::refresh() {
    if (window != NULL) wrefresh(window);
}

//MAKE SURE TO CALL THIS BEFORE USING ANYTHING ELSE
void ConsoleWindow::init() {
    window = newwin(height, width, x, y);
}
