cmake_minimum_required(VERSION 3.20)
set(GAME_NAME project-1)
project(${GAME_NAME} LANGUAGES C CXX)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/**)
add_executable(${GAME_NAME} ${GAME_SOURCES})
target_link_libraries(${GAME_NAME} PRIVATE zephyrion-engine)

set_target_properties(${GAME_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLEAN_BIN_DIR})
add_custom_command(TARGET ${GAME_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/project/assets"
        "${CLEAN_BIN_DIR}/assets"
)