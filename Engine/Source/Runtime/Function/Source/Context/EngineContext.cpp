#include <Function/Context/EngineContext.hpp>
#include <Resource/AssetManager/AssetManager.hpp>

namespace Engine {

bool EngineContext::instantiated = false;

bool EngineContext::Initialize() {
    _AssetManager = FSharedPointer<AssetManager>(new AssetManager());
    if (!_AssetManager->Initialize()) {
        PRINT_ERROR("EngineContext::Initialize: AssetManager initialization failed.");
        return 0;
    }
    return 1;
}
// Guarenteed to be called after the initialization
void EngineContext::Destroy() {
    _AssetManager->Destroy();
}
}