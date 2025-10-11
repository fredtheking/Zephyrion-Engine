cmake_minimum_required(VERSION 3.20)
set(ENGINE_NAME cobalt-engine)
project(${ENGINE_NAME} LANGUAGES CXX)

include(FetchContent)



FetchContent_Declare(
        sdl3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-3.2.24
        GIT_PROGRESS   TRUE
        GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(sdl3)


FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        v1.92.1
        GIT_PROGRESS   TRUE
        GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(imgui)
set(IMGUI_DIR ${CMAKE_BINARY_DIR}/_deps/imgui-src)
file(GLOB IMGUI_SOURCES
        ${IMGUI_DIR}/*.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)
target_link_libraries(imgui PUBLIC SDL3::SDL3)


FetchContent_Declare(
        stduuid
        GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
        GIT_TAG        v1.2.3
        GIT_PROGRESS   TRUE
        GIT_SHALLOW    TRUE
        GIT_DEPTH      1
)
FetchContent_MakeAvailable(stduuid)



file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cobalt/**)
add_library(${ENGINE_NAME} STATIC ${ENGINE_SOURCES})
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${ENGINE_NAME} PUBLIC SDL3::SDL3 imgui stduuid)
add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/engine/res"
        "${CLEAN_BIN_DIR}/assets/engine"
)