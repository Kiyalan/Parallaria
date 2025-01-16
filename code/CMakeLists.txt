cmake_minimum_required(VERSION 3.10)
project(
    Parallaria
    VERSION 1.0.0
    DESCRIPTION "A simple tiny duplicate of Terraria"
)

add_executable(main main.cpp)
# link opengl libraries
add_subdirectory(opengl)
target_link_libraries(main PRIVATE opengl)