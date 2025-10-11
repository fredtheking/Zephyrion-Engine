cmake_minimum_required(VERSION 3.20)
set(SOLUTION_NAME CobaltProject)
project(${SOLUTION_NAME} LANGUAGES CXX)
set(CLEAN_BIN_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(engine)
add_subdirectory(project)