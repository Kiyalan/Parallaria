#ifndef ENGINE_ASSET_MANAGER_INCLUDED
#define ENGINE_ASSET_MANAGER_INCLUDED

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <env.hpp>

namespace Engine {

class AssetManager {
private:
    std::unordered_map<std::string, std::shared_ptr<void>> _assetTable;
public:
    std::filesystem::path resourceFolder;
public:
    AssetManager() = default;
    ~AssetManager() = default;
public:
    bool Initialize();
    void Destroy();
    template<typename AssetClass>
    bool DeserializeAsset(std::filesystem::path, std::shared_ptr<AssetClass>&);
    template<typename AssetClass>
    void ReleaseAsset(std::filesystem::path);
};

}

#endif // ENGINE_ASSET_MANAGER_INCLUDED









