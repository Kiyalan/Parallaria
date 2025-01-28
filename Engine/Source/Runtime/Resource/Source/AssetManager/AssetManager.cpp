#include <AssetManager/AssetManager.hpp>

namespace Engine {

AssetManager gAssetManager;

bool AssetManager::Initialize() {
    // initialize file path and GUID mapping in the asset table
    return true;
}

void AssetManager::Destroy() {

}

bool AssetManager::LoadAsset(FString iGUID) {
    auto node = _AssetTable.find(iGUID);
    if (node == _AssetTable.end()) {
        PRINT_ERROR("AssetManager::LoadAsset: GUID not found in table.", iGUID);
        return false;
    }
}

void AssetManager::UnloadAsset() {
    
}


}