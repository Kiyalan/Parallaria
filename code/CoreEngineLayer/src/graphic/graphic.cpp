#include <glad/glad.h>
#include <graphic/graphic.hpp>
#include <window/window.hpp>

namespace Engine {

void Graphic::GraphicBindWindow(Window& window){
    _parentWindow = window._windowHandle;
}

bool Graphic::Initialize(){
    if (_parentWindow == nullptr)
        throw "No window context binded";
    glfwMakeContextCurrent(_parentWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return 0;
    return 1;
}

void Graphic::Render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(_parentWindow);
}

}