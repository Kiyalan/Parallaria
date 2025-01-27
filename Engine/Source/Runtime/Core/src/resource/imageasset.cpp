#include <resource/imageasset.hpp>
#include <resource/assetmanager.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Engine {
bool ImageAsset::Load(FString absPath){
    PRINT_LOG("ImageAsset at", _fileAbsolutePath = absPath, "begins to load.");
    _content = stbi_load(absPath.c_str(), &_size.x, &_size.y, &_channels, 0);
    if (!_content) {
        PRINT_ERROR("ImageAsset loading failure at ", absPath);
        return 0;
    }
    PRINT_LOG("ImageAsset at", absPath, "successfully loaded.");
    return 1;
}

void ImageAsset::Unload(){
    if (!_content) {
        PRINT_ERROR("You cannot unload ImageAsset at", _fileAbsolutePath, "before loading it.");
        return;
    }
    stbi_image_free(_content);
    _content = nullptr;
}
}