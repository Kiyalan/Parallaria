
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
            "src/Development/Assert/Assert.cpp"
)

add_library(CoreLayer STATIC ${srcfile})
target_include_directories(CoreLayer PUBLIC include)

# Link OpenGL
if (TARGET OpenGLLib)
    target_link_libraries(CoreLayer PRIVATE OpenGLLib)
else ()
    message(FATAL_ERROR "OpenGLLib not found when linking CoreLayer!")
endif ()
# Link STB
if (TARGET STBLib)
    target_link_libraries(CoreLayer PRIVATE STBLib)
else ()
    message(FATAL_ERROR "STBLib not found when linking CoreLayer!")
endif ()
# Link SDL
if (TARGET SDL3Lib)
    target_link_libraries(CoreLayer PRIVATE SDL3Lib)
else ()
    message(FATAL_ERROR "SDL3Lib not found when linking CoreLayer!")
endif ()
