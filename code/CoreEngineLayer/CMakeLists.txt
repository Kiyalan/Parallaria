
set(srcfile src/utility.cpp
            src/window/window.cpp
            src/graphic/graphic.cpp
            src/graphic/shader.cpp
            # src/graphic/renderable.cpp
            src/input/input.cpp
            src/time/frame.cpp
            src/resource/asset.cpp
            src/resource/assetmanager.cpp
            src/resource/imageasset.cpp
)

add_library(coreEngine STATIC ${srcfile})

target_link_libraries(coreEngine PRIVATE opengl)
target_link_libraries(coreEngine PRIVATE resourceLoader)
target_include_directories(coreEngine PUBLIC include)
