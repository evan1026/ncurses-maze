#include <ncurses.h>

#include "ConsoleWindow.h"
#include "Point.h"

ConsoleWindow::ConsoleWindow(int _x, int _y, int _width, int _height) :
            width(_width), height(_height), x(_x), y(_y) {
    window = newwin(height, width, y, x);
}

ConsoleWindow::ConsoleWindow(const ConsoleWindow& c) :
            width(c.width), height(c.height), x(c.x), y(c.y) {
    window = newwin(height, width, y, x);
}

ConsoleWindow::ConsoleWindow(ConsoleWindow&& c) :
            width(c.width), height(c.height), x(c.x), y(c.y) {
    window = c.window;
    c.window = nullptr;
}

ConsoleWindow::~ConsoleWindow() {
    if (window != nullptr) delwin(window);
}

ConsoleWindow& ConsoleWindow::operator=(const ConsoleWindow& c) {
    width = c.width;
    height = c.height;
    x = c.x;
    y = c.y;

    if (window != nullptr) delwin(window);
    window = newwin(height, width, y, x);

    return *this;
}

ConsoleWindow& ConsoleWindow::operator=(ConsoleWindow&& c) {
    width = c.width;
    height = c.height;
    x = c.x;
    y = c.y;

    if (window != nullptr) delwin(window);
    window = c.window;
    c.window = nullptr;

    return *this;
}

void ConsoleWindow::set(int x, int y, chtype c) {
    if (window != nullptr) mvwaddch(window, y, x, c);
}

void ConsoleWindow::set(Point p, chtype c) {
    set(p.x, p.y, c);
}

chtype ConsoleWindow::get(int x, int y) {
    if (window != nullptr) return mvwgetch(window, y, x);
    return 0;
}

chtype ConsoleWindow::get(Point p) {
    return get(p.x, p.y);
}

void ConsoleWindow::drawBox() {
    if (window != nullptr) box(window, 0, 0);
}

void ConsoleWindow::refresh() {
    if (window != nullptr) wrefresh(window);
}

int ConsoleWindow::getWidth() {
    return width;
}

int ConsoleWindow::getHeight() {
    return height;
}

int ConsoleWindow::getX() {
    return x;
}

int ConsoleWindow::getY() {
    return y;
}
