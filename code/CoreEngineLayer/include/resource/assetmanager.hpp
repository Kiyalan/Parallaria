#ifndef ENGINE_ASSETMANAGER_INCLUDED
#define ENGINE_ASSETMANAGER_INCLUDED
#include <utility.hpp>

namespace Engine {

class Asset;
enum class EAssetType;

class AssetManager {
private:
    static FHashTable<FString, FSharedPointer<Asset> > _assetTable;
public:
    /*
        Combine file relative path, asset folder and project folder to form the complete absolute path
    */
    static FString assetFolder;
    static FString projectFolder;
    /*
        Request the pointer to a Asset specified by its relative file path
    */
    static FSharedPointer<const Asset> RequestAsset(EAssetType, FString);
public:
    static bool Initialize();
};

}


#endif