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

# Add subdirectories
add_subdirectory(Source/ThirdParty)
add_subdirectory(Source/Runtime/Core)
add_subdirectory(Source/Runtime/Resource)
add_subdirectory(Source/Runtime/Function)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
target_compile_definitions(CoreLayer PRIVATE ENGINE_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(ResourceLayer PRIVATE ENGINE_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}")

# Add executables
add_executable(Main main.cpp)
add_executable(PatrickStar patrickstar.cpp)

# link test executables with Core Layer
target_link_libraries(Main PRIVATE CoreLayer)
target_link_libraries(PatrickStar PRIVATE CoreLayer)

# temporary linkging for bad abstaction
target_link_libraries(Main PRIVATE OpenGLLib)
target_link_libraries(PatrickStar PRIVATE OpenGLLib)
target_link_libraries(Main PRIVATE SDL3Lib)
target_link_libraries(PatrickStar PRIVATE SDL3Lib)