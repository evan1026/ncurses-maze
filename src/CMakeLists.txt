file(RELATIVE_PATH CURR_DIR ${ROOT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("Adding ${CURR_DIR}")

set(SOURCES "${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" CACHE STRING "Sources for project" FORCE)

add_subdirectory("maze")
add_subdirectory("generation")
add_subdirectory("rendering")

