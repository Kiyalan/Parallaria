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
add_executable(patrickStar patrickstar.cpp)

# load SDL
include_directories(${CMAKE_SOURCE_DIR}/SDL/include)
target_link_libraries(main PRIVATE ${CMAKE_SOURCE_DIR}/SDL/lib/SDL3/SDL3.a ${CMAKE_SOURCE_DIR}/SDL/lib/SDL3_mixer/SDL3_mixer.a)

# load OpenGL library
add_subdirectory(opengl)
target_link_libraries(main PRIVATE opengl)
target_link_libraries(patrickStar PRIVATE opengl)

# load resourLoader library
add_subdirectory(resloader)

# load Core Engine Layer
add_subdirectory(CoreEngineLayer)
target_link_libraries(main PRIVATE coreEngine)
target_link_libraries(patrickStar PRIVATE coreEngine)
target_link_libraries(main PRIVATE coreEngine)

#target_link_libraries(main PRIVATE SDL3 SDL3_mixer)