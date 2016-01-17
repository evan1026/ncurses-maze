#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Maze.h"
#include "MazeCell.h"
#include "Point.h"
#include "PrimsMazeGenerator.h"

//Making these 2 instead of 1 allows us to move between actual maze cells,
//rather than cells and walls
Point PrimsMazeGenerator::directions[] = {Point(2,0), Point(-2,0), Point(0,2), Point(0,-2)};
#define DIRECTION_COUNT 4

//Returns whether the specified point is in the portion of the maze that has been generated
bool PrimsMazeGenerator::isInMaze(Point p, Maze& m) {
    return p == start || m.isConnected(p);
}

//Does removal in constant time by swapping the last element down to replace the element to be removed
//and then using pop_back, which effectively just causes the vector to think it's 1 element smaller
//I'm pretty sure the underlying array is not reallocated, and if it is, it's a rare occurance
//(i.e., if this isn't actually constant, it's amorphized constant)
void PrimsMazeGenerator::removePoint(int index, std::vector<Point>& container) {
    if (!container.empty() && index < container.size()) {
        container[index] = container[container.size() - 1];
        container.pop_back();
    }
}

bool PrimsMazeGenerator::vecContains(Point p, std::vector<Point>& container) {
    return std::find(container.begin(), container.end(), p) != container.end();
}

void PrimsMazeGenerator::generate(Maze& m) {

    start = m.start;

    std::vector<Point> points;
    srand(time(NULL));

    for (Point d : directions) {
        Point newPoint = start + d;
        if (m.get(newPoint).type == MazeCell::Type::OPEN) {
            points.push_back(newPoint);
        }
    }

    while (!points.empty()) {
        int pointIndex;
        int directionIndex;
        do {
            pointIndex = rand() % points.size();
            directionIndex = rand() % DIRECTION_COUNT;
            for (int i = 0; i < DIRECTION_COUNT; ++i) {
                int possibleDirectionIndex = (directionIndex + i) % DIRECTION_COUNT;
                if (isInMaze(points[pointIndex] + directions[possibleDirectionIndex], m)) {
                    directionIndex = possibleDirectionIndex;
                    break;
                }
            }
            if (directionIndex == -1) {
                removePoint(pointIndex, points);
            }
        } while (!points.empty() && directionIndex == -1);

        if (directionIndex != -1) {
            Point curr = points[pointIndex];
            Point wall = curr + directions[directionIndex] / 2;

            removePoint(pointIndex, points);
            m.setType(wall, MazeCell::Type::OPEN);

            for (Point d : directions) {
                Point adjacentPoint = curr + d;
                if (!isInMaze(adjacentPoint, m) && m.get(adjacentPoint).type == MazeCell::Type::OPEN &&
                        !vecContains(adjacentPoint, points)) {
                    points.push_back(adjacentPoint);
                }
            }
        }
    }
}
