#include <utility.hpp>
#include <window/window.hpp>
#include <graphic/graphic.hpp>
#include <input/input.hpp>
#include <time/frame.hpp>
#include <time/time.hpp>
#include <graphic/renderable.hpp>
#include <resource/assetmanager.hpp>
#include <resource/imageasset.hpp>

int main() {
    if (!glfwInit()) {
        PRINT_ERROR("GLFW initialization failed");
        throw std::exception();
    }
    Engine::AssetManager::projectFolder = "D:/GuaGua/Game/Parallaria/";
    Engine::AssetManager::Initialize();
    Engine::WindowSetting windowSetting;
    windowSetting.displayState = Engine::EWindowDisplayState::Windowed;
    windowSetting.windowWidth = 1440;
    windowSetting.windowHeight = 900;
    Engine::Window window {windowSetting};
    if (!window.Initialize()) {
        throw std::exception();
    }
    Engine::Graphic graphic;
    graphic.GraphicBindWindow(window);
    if (!graphic.Initialize())
        throw std::exception();
    Engine::Input::Init(window);

    FSharedPointer<Engine::RenderableImage2D> patrick {new Engine::RenderableImage2D};
    patrick->SetImageAsset("PatrickStar.jpg");
    patrick->SetShader(graphic.GetDefaultImageShader());
    FStaticArray<FReal, 20> ver {
         0.35f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.35f,  0.5f, 0.0f, 0.0f, 0.0f,
        -0.35f, -0.5f, 0.0f, 0.0f, 1.0f,
         0.35f, -0.5f, 0.0f, 1.0f, 1.0f
    };
    patrick->_vertexAttributeArray = ver;
    patrick->Initialize();

    FReal64 previousTime = Engine::Time::GetCurrentTime();
    FReal64 lagTime = .0;
    while (!window.ShouldWindowClose()) {
        FReal64 currentTime = Engine::Time::GetCurrentTime();
        FReal64 elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lagTime += elapsedTime;
        while (lagTime >= Engine::Frame::secondsPerFrame) {
            lagTime -= Engine::Frame::secondsPerFrame;
            graphic.ClearRenderable();
            // process input and window event 
            glfwPollEvents();
            graphic.AddRenderable(patrick);
        }
        graphic.Render();
    }

    window.Destroy();
    glfwTerminate();
    return 0;
}