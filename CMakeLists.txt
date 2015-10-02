cmake_minimum_required(VERSION 2.8)

project(ncurses-learning)

set(SOURCE_DIR "src")

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

add_executable(mazegame "${SOURCE_DIR}/main.cpp"
                        "${SOURCE_DIR}/Maze.cpp"
                        "${SOURCE_DIR}/MazeCells.cpp")

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
target_link_libraries(mazegame ${CURSES_LIBRARIES})
include_directories(${CURSES_INCLUDE_DIR})
