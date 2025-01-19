#include <GLFW/glfw3.h>
#include <window/window.hpp>
#include <graphic/graphic.hpp>
#include <input/input.hpp>

// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

int main() {
    if (!glfwInit())
        throw "Failed to start GLFW";

    Engine::WindowSetting windowSetting;
    windowSetting.displayState = Engine::EWindowDisplayState::Windowed;
    windowSetting.windowWidth = 1440;
    windowSetting.windowHeight = 900;
    Engine::Window window {windowSetting};
    if (!window.Initialize())
        throw "Window failed to initialized";
    Engine::Graphic graphic;
    graphic.GraphicBindWindow(window);
    if (!graphic.Initialize())
        throw "Graphic failed to initialized";

    
    glViewport(0, 0, 1440, 900);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    Engine::Input::Init(window);
    while (!window.ShouldWindowClose()) {
        glfwPollEvents();
        
        graphic.Render();
    }

    window.Destroy();
    
    glfwTerminate();
    return 0;
}