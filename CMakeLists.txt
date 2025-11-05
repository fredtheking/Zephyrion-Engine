cmake_minimum_required(VERSION 3.20)
set(SOLUTION_NAME ZephyrionProject)
project(${SOLUTION_NAME} LANGUAGES CXX)

set(ENGINE_NAME zephyrion-engine)
set(SANDBOX_NAME sandbox-project)
set(EDITOR_NAME zephyrion-editor)

set(CLEAN_BIN_DIR ${CMAKE_SOURCE_DIR}/build)
set(SANDBOX_CLEAN_BIN_DIR ${CLEAN_BIN_DIR}_sandbox)
set(EDITOR_CLEAN_BIN_DIR ${CLEAN_BIN_DIR}_editor)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(engine)
add_subdirectory(sandbox)
add_subdirectory(editor)