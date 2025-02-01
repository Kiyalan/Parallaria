add_subdirectory(SDL)

add_subdirectory(OpenGL)

add_library(STBLib INTERFACE)
target_include_directories(STBLib INTERFACE "STB")

add_library(RapidJSONLib INTERFACE)
target_include_directories(RapidJSONLib INTERFACE "RapidJSON/include")

add_library(GLILib INTERFACE)
target_include_directories(GLILib INTERFACE "GLI")
target_link_libraries(GLILib INTERFACE OpenGLLib)
