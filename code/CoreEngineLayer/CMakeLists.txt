
set(srcfile src/window/window.cpp)

add_library(coreengine STATIC ${srcfile})

target_include_directories(coreengine PUBLIC include)
