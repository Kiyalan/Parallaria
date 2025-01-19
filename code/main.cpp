#include <GLFW/glfw3.h>
#include <window/window.hpp>
#include <graphic/graphic.hpp>
#include <input/input.hpp>
#include <timer/frame.hpp>

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
    Engine::Input::Init(window);

    FReal64 previousTime = glfwGetTime();
    FReal64 lagTime = .0;
    while (!window.ShouldWindowClose()) {
        FReal currentTime = glfwGetTime();
        FReal elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lagTime += elapsedTime;
        while (lagTime >= Engine::Frame::secondsPerFrame) {
            lagTime -= Engine::Frame::secondsPerFrame;
            // process input and window event 
            glfwPollEvents();
            // update 
        }
        graphic.Render();
    }
    
    window.Destroy();
    glfwTerminate();
    return 0;
}