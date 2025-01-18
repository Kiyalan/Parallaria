#include <window/window.hpp>

namespace Engine {

Window::Window(WindowSetting iWindowSetting) :_windowSetting{iWindowSetting} {
    _bWindowInitialized = 0;
    _windowHandle = nullptr;
}

Window::~Window(){
    
}

bool Window::Initialize(){
    if (_bWindowInitialized)
        return 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    // Do not support multi-monitor 
    switch (static_cast<int>(_windowSetting.displayState)) {
        case static_cast<int>(EWindowDisplayState::WindowedFullScreen): {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            _windowHandle = glfwCreateWindow(mode->width, mode->height, _windowSetting.windowTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
            break;
        }
        case static_cast<int>(EWindowDisplayState::FullScreen):
            _windowHandle = glfwCreateWindow(0, 0, _windowSetting.windowTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
            break;
        case static_cast<int>(EWindowDisplayState::Windowed):
            _windowHandle = glfwCreateWindow(_windowSetting.windowWidth, _windowSetting.windowHeight, _windowSetting.windowTitle.c_str(), nullptr, nullptr);
            break;
    }
    _bWindowInitialized = 1;
    return 1;
}

void Window::Destroy(){
    if (_bWindowInitialized) {
        glfwDestroyWindow(_windowHandle);
        _bWindowInitialized = 0;
    }
}

bool Window::ShouldWindowClose() const {
    if (!_bWindowInitialized) {
        // Throw a exception because the window hasn't been initialized
    }
    return glfwWindowShouldClose(_windowHandle);
}

void Window::SetWindowSetting(WindowSetting iWindowSetting){
    /*
        Support operations to change
            - Window display mode
            - for windowed mode:
                - Window size
                - Window title

    */
    if (iWindowSetting.displayState == _windowSetting.displayState) {
        if (iWindowSetting.displayState == EWindowDisplayState::Windowed) {
            glfwSetWindowTitle(_windowHandle, iWindowSetting.windowTitle.c_str());
            glfwSetWindowSize(_windowHandle, iWindowSetting.windowWidth, iWindowSetting.windowHeight);
        }
    }
    else switch (static_cast<int>(iWindowSetting.displayState)) {
        case static_cast<int>(EWindowDisplayState::WindowedFullScreen): {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(_windowHandle, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
            break;
        }
        case static_cast<int>(EWindowDisplayState::FullScreen): {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(_windowHandle, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
            break;
        }
        case static_cast<int>(EWindowDisplayState::Windowed):
            const int placex = 0, placey = 0;
            glfwSetWindowMonitor(_windowHandle, nullptr, placex, placey, iWindowSetting.windowWidth, iWindowSetting.windowHeight, 0);
    }
    _windowSetting = iWindowSetting;
}

}
