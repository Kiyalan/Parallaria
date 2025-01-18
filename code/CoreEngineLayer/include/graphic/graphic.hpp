#include <GLFW/glfw3.h>

#ifndef ENGINE_GRAPHIC_INCLUDED
#define ENGINE_GRAPHIC_INCLUDED

namespace Engine {

class Window;

class Graphic {
private:
    GLFWwindow* _parentWindow;
public:
    Graphic(){;}
    ~Graphic(){;}
    void GraphicBindWindow(Window&);
    bool Initialize();
    void Render();
};





}

#endif