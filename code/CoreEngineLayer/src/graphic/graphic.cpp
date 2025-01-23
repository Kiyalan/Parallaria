#include <glad/glad.h>
#include <GL/gl.h>
#include <graphic/graphic.hpp>
#include <window/window.hpp>
#include <resource/assetmanager.hpp>
#include <time/time.hpp>
#include <iostream>
#include <cmath>

namespace Engine {

void Graphic::GraphicBindWindow(Window& window){
    _parentWindow = window._windowHandle;
}

bool Graphic::Initialize(){
    PRINT_LOG("Graphic initailization begins.");
    if (_parentWindow == nullptr) {
        PRINT_ERROR("No window context binded.");
        return 0;
    }
    glfwMakeContextCurrent(_parentWindow);
    // Enable vertical synchronization
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        PRINT_ERROR("GLAD load failed.");
        return 0;
    }
    // Initialize default image and polygon shader
    _defaultImageShader = FSharedPointer<Shader>(new Shader);
    if (!(_defaultImageShader->LoadShaderSource(EShaderType::VertexShader, AssetManager::projectFolder + "code/CoreEngineLayer/src/graphic/image.vert")
        && _defaultImageShader->LoadShaderSource(EShaderType::FragmentShader, AssetManager::projectFolder + "code/CoreEngineLayer/src/graphic/image.frag")
        && _defaultImageShader->Initialize())) {
        PRINT_ERROR("Graphic default image shader initialization failed.");
        return 0;
    }
    _defaultPolygonShader = FSharedPointer<Shader>(new Shader);
    if (!(_defaultPolygonShader->LoadShaderSource(EShaderType::VertexShader, AssetManager::projectFolder + "code/CoreEngineLayer/src/graphic/polygon.vert")
        && _defaultPolygonShader->LoadShaderSource(EShaderType::FragmentShader, AssetManager::projectFolder + "code/CoreEngineLayer/src/graphic/polygon.frag")
        && _defaultPolygonShader->Initialize())) {
        PRINT_ERROR("Graphic default polygon shader initialization failed.");
        return 0;
    }
    PRINT_LOG("Graphic default shader initalization completed");
    PRINT_LOG("Graphic initialization completed.");
    return 1;
}

void Graphic::AddRenderable(FSharedPointer<Renderable> obj){
    _renderableQueue.push(obj);
}

void Graphic::ClearRenderable(){
    while (!_renderableQueue.empty())
        _renderableQueue.pop();
}

void Graphic::Render(){
    // glClearColor(1.f, 1.f, 1.f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    while (!_renderableQueue.empty()) {
        _renderableQueue.front()->Render();
        _renderableQueue.pop();
    }
    glfwSwapBuffers(_parentWindow);
}

}