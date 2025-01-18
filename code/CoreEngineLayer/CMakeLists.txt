
set(srcfile src/window/window.cpp src/graphic/graphic.cpp)

add_library(coreengine STATIC ${srcfile})

target_link_libraries(coreengine PRIVATE opengl)
target_include_directories(coreengine PUBLIC include)
