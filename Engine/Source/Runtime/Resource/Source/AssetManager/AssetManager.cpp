#include <type_traits>
#include <utility>
#include <Development/Assert/Assert.hpp>
#include <Development/Log/Log.hpp>
#include <Resource/AssetManager/AssetManager.hpp>


namespace Engine {



bool AssetManager::Initialize() {
    // initialize file path and GUID mapping in the asset table
    return true;
}

void AssetManager::Destroy() {

}

/**
 * @param path path can be absolute or relative ONLY to the resource directory
 */
template<typename AssetClass>
bool AssetManager::DeserializeAsset(std::filesystem::path path, std::shared_ptr<AssetClass>& asset) {
    if (path.is_relative())
        path = resourceFolder / path;
    auto& iter = _assetTable.find(path.string().c_str());
    if (iter != _assetTable.end()) {
        // Developing Assertion: Asset type mismatch
        // DYNAMIC_ASSERT(std::is_same_v<AssetClass, decltype(*iter->second)>>, "AssetManager::DeserializeAsset: Asset type mismatch.">);
        asset = std::static_pointer_cast<AssetClass>(iter->second);
        return true;
    }
    iter->second = asset = std::make_shared<AssetClass>();
    return asset->template Serialize<0>(path);
}  

/**
 * Once called, the asset designated by the path will be released. Any pointers to the asset will be invalidated.
 * @param path path can be absolute or relative ONLY to the resource directory
 */
template<typename AssetClass>
void AssetManager::ReleaseAsset(std::filesystem::path path) {
    if (path.is_relative())
        path = resourceFolder / path;
    auto& iter = _assetTable.find(path.string().c_str());
    // if (iter == _assetTable.end()) return;
    DYNAMIC_ASSERT(iter != _assetTable.end(), "AssetManager::ReleaseAsset: Asset is not loaded even.");
    delete std::static_pointer_cast<AssetClass>(iter->second);
    _assetTable.erase(iter);
}


}