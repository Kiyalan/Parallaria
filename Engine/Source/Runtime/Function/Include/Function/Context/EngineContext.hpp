#ifndef ENGINE_ENGINE_CONTEXT_INCLUDED
#define ENGINE_ENGINE_CONTEXT_INCLUDED

#include <utility.hpp>

namespace Engine {

class AssetManager;

class EngineContext final {
private:
    FSharedPointer<AssetManager> _AssetManager {nullptr};
public:
    inline FSharedPointer<AssetManager> GetAssetManager() const {return _AssetManager;};
public:
    bool Initialize();
    void Destroy();
public:
    static bool instantiated;
    EngineContext(){
        ASSERT(!instantiated);
        instantiated = true;
    };
    ~EngineContext(){instantiated = false;};
    EngineContext(const EngineContext&) = delete;
    EngineContext& operator=(const EngineContext&) = delete;
    EngineContext(EngineContext&&) = delete;
    EngineContext& operator=(EngineContext&&) = delete;
};

}
#endif // ENGINE_ENGINE_CONTEXT_INCLUDED