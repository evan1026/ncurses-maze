file(RELATIVE_PATH CURR_DIR ${ROOT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("Adding ${CURR_DIR}")

set(SOURCES "${SOURCES} ${CURR_DIR}/ConsoleMazeRenderer.cpp
                        ${CURR_DIR}/PseudoConsoleWindow.cpp
                        ${CURR_DIR}/ConsoleWindow.cpp
                        ${CURR_DIR}/ConsoleViewport.cpp"
                        CACHE STRING "Sources for project" FORCE)
