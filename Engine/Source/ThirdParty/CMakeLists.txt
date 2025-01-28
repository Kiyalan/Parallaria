add_subdirectory(SDL)

add_subdirectory(OpenGL)

add_library(STBLib INTERFACE)
target_include_directories(STBLib INTERFACE "STB")

add_library(RapidJSONLib INTERFACE)
target_include_directories(RapidJSONLib INTERFACE "RapidJSON/include")
