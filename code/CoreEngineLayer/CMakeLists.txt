
set(srcfile src/utility.cpp
            src/window/window.cpp
            src/graphic/graphic.cpp
            src/graphic/shader.cpp
            src/graphic/renderable.cpp
            src/input/input.cpp
            src/time/frame.cpp
            src/resource/asset.cpp
            src/resource/assetmanager.cpp
            src/resource/imageasset.cpp
            src/resource/audioasset.cpp
)

add_library(coreEngine STATIC ${srcfile})

target_link_libraries(coreEngine PRIVATE opengl)
target_link_libraries(coreEngine PRIVATE resourceLoader)
target_link_libraries(coreEngine PRIVATE ${CMAKE_SOURCE_DIR}/SDL/lib/SDL3/SDL3.a ${CMAKE_SOURCE_DIR}/SDL/lib/SDL3_mixer/SDL3_mixer.a)

target_include_directories(coreEngine PUBLIC include)

if(WIN32)
    target_link_libraries(coreEngine PRIVATE winmm imm32 setupapi version)
endif()
