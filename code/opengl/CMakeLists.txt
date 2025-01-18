
# since GLM and GLFW has its own CMakeLists.txt, only GLAD will be included manually
set(srcfile glad/src/glad.c)
set(incdir glad/include)
add_library(opengl STATIC ${srcfile})
target_include_directories(opengl PUBLIC ${incdir})
# link GLFW
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(glfw)
target_link_libraries(opengl PUBLIC glfw)
# link GLM
set(GLM_BUILD_TESTS OFF)
add_subdirectory(glm)
target_link_libraries(opengl PUBLIC glm::glm)
# link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(opengl PUBLIC OpenGL::GL)
