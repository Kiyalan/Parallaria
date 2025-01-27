add_subdirectory(SDL)

add_subdirectory(OpenGL)

add_library(STBLib STATIC placeholder.cpp)
target_include_directories(STBLib PUBLIC STB)
