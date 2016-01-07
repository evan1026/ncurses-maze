cmake_minimum_required(VERSION 2.8)

project(ncurses-maze)

set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")
set(EXECUTABLE_NAME mazegame)
set(DEBUG true)

if(DEBUG)
    set(CMAKE_CXX_FLAGS "-O0 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -std=c++11 -Wall -Werror ${CMAKE_CXX_FLAGS}")
    #set(CMAKE_CXX_FLAGS "-fsanitize=memory ${DEBUG_FLAGS}")
    #set(CMAKE_CXX_FLAGS "-fsanitize=address ${DEBUG_FLAGS}")
else(DEBUG)
    set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
endif(DEBUG)

set(SOURCES "" CACHE STRING "Sources for project" FORCE)
get_filename_component(ROOT_DIR_ABS ${SOURCE_DIR} ABSOLUTE)
get_filename_component(ROOT_DIR ${ROOT_DIR_ABS} DIRECTORY)
add_subdirectory("${SOURCE_DIR}")

include_directories(${INCLUDE_DIR})

string(REPLACE "\n" " " SOURCES_WITHOUT_NL ${SOURCES})
set(SOURCES ${SOURCES_WITHOUT_NL} CACHE STRING "Sources for project" FORCE)
string(REPLACE " " ";" SOURCE_LIST ${SOURCES})
add_executable(${EXECUTABLE_NAME} ${SOURCE_LIST})

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} ${CURSES_LIBRARIES})
include_directories(${CURSES_INCLUDE_DIR})
