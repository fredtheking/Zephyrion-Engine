cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME} LANGUAGES C CXX)

file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/**)
add_executable(${EDITOR_NAME} ${EDITOR_SOURCES})
target_link_libraries(${EDITOR_NAME} PRIVATE zephyrion-engine)

set_target_properties(${EDITOR_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EDITOR_CLEAN_BIN_DIR})
add_custom_command(TARGET ${EDITOR_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/editor/res"
        "${EDITOR_CLEAN_BIN_DIR}/res"
)