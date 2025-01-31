#include <filesystem>
#include <resource/assetmanager.hpp>
#include <resource/imageasset.hpp>
#include <resource/audioasset.hpp>
#include <utility.hpp>

namespace Engine {

// This default value is current working directory
FString AssetManager::assetFolder {"Engine/Resource/"};
FString AssetManager::projectFolder {"project folder unitialized"};

FHashTable<FString, FSharedPointer<Asset> > AssetManager::_assetTable;

bool AssetManager::Initialize() {
    PRINT_LOG("AssetManager initialization begins.");
    PRINT_LOG("AssetManager initialization completed.");
    return 1;
}

FSharedPointer<const Asset> AssetManager::RequestAsset(EAssetType type, FString path){
    if (_assetTable[path]) return _assetTable[path];
    switch (type) {
        case EAssetType::Image:
            _assetTable[path] = FSharedPointer<Asset>(new ImageAsset);
            break;
        case EAssetType::Sound:
            _assetTable[path] = FSharedPointer<Asset>(new Sound);
            break;
        case EAssetType::Music:
            _assetTable[path] = FSharedPointer<Asset>(new Music);
            break;
    }
    if (_assetTable[path] == nullptr) {
        PRINT_ERROR("Asset class allocation failed.");
        return nullptr;
    }
    FString absPath = projectFolder + assetFolder + path;
    if (!_assetTable[path]->Load(absPath)) {
        PRINT_ERROR("Failed to load asset at", path);
        _assetTable[path].reset();
    }
    return _assetTable[path];
}

}