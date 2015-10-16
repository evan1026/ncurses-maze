cmake_minimum_required(VERSION 2.8)

project(ncurses-learning)

set(SOURCE_DIR "src")

#set(CMAKE_CXX_FLAGS "-O1 -std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

#######################
# DEBUG BUILD OPTIONS #
#######################
set(DEBUG_FLAGS "-O0 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
#set(DEBUG_FLAGS "-fsanitize=memory ${DEBUG_FLAGS}")
#set(DEBUG_FLAGS "-fsanitize=address ${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS ${DEBUG_FLAGS})


add_executable(mazegame "${SOURCE_DIR}/ColorMazeRenderer.cpp"
                        "${SOURCE_DIR}/main.cpp"
                        "${SOURCE_DIR}/Maze.cpp"
                        "${SOURCE_DIR}/MazeCells.cpp"
                        "${SOURCE_DIR}/MazeRenderer.cpp")

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
target_link_libraries(mazegame ${CURSES_LIBRARIES})
include_directories(${CURSES_INCLUDE_DIR})
