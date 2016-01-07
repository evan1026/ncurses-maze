#include <ncurses.h>
#include <vector>

#include "PseudoConsoleWindow.h"

PseudoConsoleWindow::PseudoConsoleWindow(int _width, int _height) : width(_width), height(_height),
                                             cells(height, std::vector< chtype > (width, 0)) {}

void PseudoConsoleWindow::set(int x, int y, chtype c) {
    cells[y][x] = c;
}

void PseudoConsoleWindow::set(Point p, chtype c) {
    set(p.x, p.y, c);
}

chtype PseudoConsoleWindow::get(int x, int y) {
    return cells[y][x];
}

chtype PseudoConsoleWindow::get(Point p) {
    return get(p.x, p.y);
}
