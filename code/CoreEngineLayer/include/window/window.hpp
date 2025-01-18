#include <GLFW/glfw3.h>
#include <env.hpp>
#include <graphic/graphic.hpp>

#ifndef ENGINE_WINDOW_INCLUDED
#define ENGINE_WINDOW_INCLUDED

namespace Engine {

enum class EWindowDisplayState {
    FullScreen,
    WindowedFullScreen, // a kind of fast and soft FullScreen
    Windowed
};

struct WindowSetting {
    EWindowDisplayState displayState = EWindowDisplayState::WindowedFullScreen;
    FString windowTitle = "Untitled";
    bool bTopmmost = 0;
    // If windowed
    FInt32 windowHeight = 1440, windowWidth = 900;
    bool bDecorated = 1;
    bool bAttracting = 0;
};

class Window {
private:
    GLFWwindow* _windowHandle;
    WindowSetting _windowSetting;
    bool _bWindowInitialized;

    // Bindings of input and graphic
    friend void InputBindWindow(Window&);
    friend void Graphic::GraphicBindWindow(Window&);
public:
    Window(WindowSetting);
    ~Window();

    bool Initialize();
    void Destroy();

    // Reflect the user's click on the close button or the system close signal.
    bool ShouldWindowClose() const;

    inline WindowSetting GetWindowSetting() const { return _windowSetting; };
    void SetWindowSetting(WindowSetting);
};

}

#endif