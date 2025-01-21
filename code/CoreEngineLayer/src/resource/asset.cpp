#include <resource/asset.hpp>

namespace Engine {
// This default value assume that the main.exe is at /build
FString Asset::assetFolder {"../resource/"};

FHashTable<FString, std::shared_ptr<Asset> > Asset::assetTable;

}