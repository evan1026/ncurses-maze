cmake_minimum_required(VERSION 2.8)

project(ncurses-learning)

set(SOURCE_DIR "src")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

add_executable(main "${SOURCE_DIR}/main.cpp")

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
target_link_libraries(main ${CURSES_LIBRARIES})
include_directories(${CURSES_INCLUDE_DIR})
