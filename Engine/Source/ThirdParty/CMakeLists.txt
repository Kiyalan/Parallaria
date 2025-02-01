add_subdirectory(SDL)

add_subdirectory(OpenGL)

add_library(STBLib INTERFACE)
target_include_directories(STBLib INTERFACE "STB")

add_library(RapidJSONLib INTERFACE)
target_include_directories(RapidJSONLib INTERFACE "RapidJSON/include")

add_library(GLILib INTERFACE)
target_include_directories(GLILib INTERFACE "GLI")
target_link_libraries(GLILib INTERFACE OpenGLLib)

add_library(AssimpLib SHARED IMPORTED GLOBAL)
set_target_properties(AssimpLib PROPERTIES 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Assimp/lib/libassimp-5.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Assimp/include"
    IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/Assimp/lib/libassimp.dll.a"
)