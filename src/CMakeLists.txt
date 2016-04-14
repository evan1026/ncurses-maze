file(RELATIVE_PATH CURR_DIR ${ROOT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("Adding ${CURR_DIR}")

set(SOURCES "${SOURCES} ${CURR_DIR}/main.cpp
                        ${CURR_DIR}/Game.cpp
                        ${CURR_DIR}/Maze.cpp
                        ${CURR_DIR}/Stats.cpp
                        ${CURR_DIR}/Statistic.cpp" CACHE STRING "Sources for project" FORCE)

add_subdirectory("rendering")
add_subdirectory("generation")
