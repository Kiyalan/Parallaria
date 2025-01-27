#ifndef ENGINE_GRAPHIC_INCLUDED
#define ENGINE_GRAPHIC_INCLUDED

#include <GLFW/glfw3.h>
#include <graphic/shader.hpp>
#include <graphic/renderable.hpp>
#include <utility.hpp>

namespace Engine {

class Window;

class Graphic {
private:
    GLFWwindow* _parentWindow = nullptr;
    FSharedPointer<Shader> _defaultPolygonShader, _defaultImageShader;
    FQueue<FSharedPointer<Renderable> > _renderableQueue;
public:
    Graphic(){;}
    ~Graphic(){;}
    void GraphicBindWindow(Window&);
    bool Initialize();
    inline FSharedPointer<const Shader> GetDefaultPolygonShader() const {return std::const_pointer_cast<const Shader>(_defaultPolygonShader);}
    inline FSharedPointer<const Shader> GetDefaultImageShader() const {return std::const_pointer_cast<const Shader>(_defaultImageShader);}
    void AddRenderable(FSharedPointer<Renderable>);
    void ClearRenderable();
    void Render();
};



}

#endif