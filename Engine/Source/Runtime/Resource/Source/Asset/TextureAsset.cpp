#include <Asset/TextureAsset.hpp>
#include <rapidjson/document.h>
#include <utility.hpp>
namespace Engine {
TextureAsset::TextureAsset(FAssetFileContext data) :
    _size{data["Width"].GetUint(), data["Height"].GetUint()},
    _channels{data["Channels"].GetUint()},
    _pixelsArraySize{_size.first * _size.second * _channels},
    _pixelsArray{new FUInt8[_pixelsArraySize]} {
    for (FUInt i = 0; i < _pixelsArraySize; ++i)
        _pixelsArray[i] = data["Pixels"][i].GetUint();
}
}