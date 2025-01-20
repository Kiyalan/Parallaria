cmake_minimum_required(VERSION 3.10)
project(
    Parallaria
    VERSION 1.0.0
    DESCRIPTION "A simple tiny duplicate of Terraria"
)

add_compile_options(-Wall -std=c++20)
set(CMAKE_CXX_COMPILER g++)

add_executable(main main.cpp)

# link opengl libraries (temporarily, after the abstraction is done, this part will be removed)
add_subdirectory(opengl)
target_link_libraries(main PRIVATE opengl)

# load Core Engine Layer
add_subdirectory(CoreEngineLayer)
target_link_libraries(main PRIVATE coreengine)