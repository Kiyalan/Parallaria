#ifndef ENGINE_ASSET_MANAGER_INCLUDED
#define ENGINE_ASSET_MANAGER_INCLUDED

#include <utility.hpp>

namespace Engine {

class Asset;

class AssetManager {
private:
    FHashTable<FString, FPair<FString, FSharedPointer<Asset>>> _AssetTable;
public:
    AssetManager() = default;
    ~AssetManager() = default;
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;
public:
    bool Initialize();
    void Destroy();
    bool LoadAsset(FString);
    void UnloadAsset();
};

}

#endif // ENGINE_ASSET_MANAGER_INCLUDED









