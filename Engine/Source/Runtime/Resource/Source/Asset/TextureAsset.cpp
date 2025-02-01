#include <GLAD/glad.h>
#include <GL/gl.h>
#include <gli/gli.hpp>
#include <stb/stb_image.h>
#include <utility>
#include <cstring>

#include <Development/Log/Log.hpp>
#include <Development/Assert/Assert.hpp>
#include <Resource/Asset/TextureAsset.hpp>

namespace Engine {

/*
Depracated: JSON constructor
TextureAsset::TextureAsset(FAssetFileContext data) :
    _size{data["Width"].GetUint(), data["Height"].GetUint()},
    _channels{data["Channels"].GetUint()},
    _pixelsArraySize{_size.first * _size.second * _channels},
    _pixelsArray{new FUInt8[_pixelsArraySize]} {
    for (FUInt i = 0; i < _pixelsArraySize; ++i)
        _pixelsArray[i] = data["Pixels"][i].GetUint();
}
*/

/**
 * @param path absolute path.
 */
bool TextureAsset::LoadFromFile(std::filesystem::path path) {
    // Developing Exception: file must exist
    if (!std::filesystem::exists(path)) {
        PRINT_ERROR("TextureAsset::LoadFromFile: File does not exist.", path);
        return false;
    }
    // Developing Exception: file format must be supported by GLI or STB
    std::string extension = path.extension().string();
    if (extension == ".dds") {
        gli::texture image = gli::load(path.string().c_str());
        if (image.empty())
            return PRINT_ERROR("TextureAsset::LoadFromFile: File could not be loaded.", path), false;
        // Restriction: only support oridinary format
        switch (image.format()) {
            case gli::format::FORMAT_RGBA8_UNORM_PACK8: _format = GL_RGBA8; break;
            case gli::format::FORMAT_RGB8_UNORM_PACK8:  _format = GL_RGB8; break;
            case gli::format::FORMAT_RG8_UNORM_PACK8:   _format = GL_RG8; break;
            case gli::format::FORMAT_R8_UNORM_PACK8:    _format = GL_R8; break;
            default:
                return PRINT_ERROR("TextureAsset::LoadFromFile: Unsupported format.", path), false;
        }
        _size = std::make_pair(image.extent().x, image.extent().y);
        _pixelsArraySize = _size.first * _size.second * image.extent().z;
        DYNAMIC_ASSERT(_pixelsArray == nullptr, "TextureAsset::LoadFromFile: Pixel array must be empty.");
        _pixelsArray = new FUInt8[_pixelsArraySize];
        std::memcpy(_pixelsArray, image.data(), _pixelsArraySize);
    } else if (extension == ".jpg"
            || extension == ".png") {
        int channels, sizeX, sizeY;
        DYNAMIC_ASSERT(_pixelsArray == nullptr, "TextureAsset::LoadFromFile: Pixel array must be empty.");
        _pixelsArray = stbi_load(path.string().c_str(), &sizeX, &sizeY, &channels, 0);
        if (!_pixelsArray) 
            return PRINT_ERROR("TextureAsset::LoadFromFile: File could not be loaded.", path), false;
        switch (channels) {
            case 4: _format = GL_RGBA8; break;
            case 3: _format = GL_RGB8; break;
            case 2: _format = GL_RG8; break;
            case 1: _format = GL_R8; break;
            default:
                return PRINT_ERROR("TextureAsset::LoadFromFile: Unsupported format.", path), false;
        }
        _size = std::make_pair(sizeX, sizeY);
        _pixelsArraySize = _size.first * _size.second * channels;
    } else 
        return PRINT_ERROR("TextureAsset::LoadFromFile: Unsupported file format.", path), false;
    return true;
}

}