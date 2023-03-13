cmake_minimum_required(VERSION 3.25)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 11)

project("sdl_opengl_framework")

add_executable(sdl_opengl_framework "main.cpp" "deps/glad/src/glad.c")
target_include_directories(sdl_opengl_framework PRIVATE "deps/glad/include")
target_link_libraries(sdl_opengl_framework SDL2)

add_subdirectory("deps/sdl" EXCLUDE_FROM_ALL)
