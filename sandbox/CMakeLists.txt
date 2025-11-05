cmake_minimum_required(VERSION 3.20)
project(${SANDBOX_NAME} LANGUAGES C CXX)

file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/**)
add_executable(${SANDBOX_NAME} ${SANDBOX_SOURCES})
target_link_libraries(${SANDBOX_NAME} PRIVATE zephyrion-engine)

set_target_properties(${SANDBOX_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SANDBOX_CLEAN_BIN_DIR})
add_custom_command(TARGET ${SANDBOX_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/sandbox/res"
        "${SANDBOX_CLEAN_BIN_DIR}/res"
)