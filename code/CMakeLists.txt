cmake_minimum_required(VERSION 3.10)
project(
    Parallaria
    VERSION 1.0.0
    DESCRIPTION "A simple tiny duplicate of Terraria"
)

# Set C++ standard 20 and enable all compilation warnings
set(CMAKE_CXX_STANDARD 20)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wall>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wextra>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wpedantic>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wshadow>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wunused>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wuninitialized>)

add_executable(main main.cpp)

# link opengl libraries (temporarily, after the abstraction is done, this part will be removed)
add_subdirectory(opengl)
target_link_libraries(main PRIVATE opengl)

# load Core Engine Layer
add_subdirectory(CoreEngineLayer)
target_link_libraries(main PRIVATE coreengine)