#ifndef ENGINE_TEXTURE_ASSET_INCLUDED
#define ENGINE_TEXTURE_ASSET_INCLUDED
#include <utility.hpp>
#include <Resource/Asset/Asset.hpp>
namespace Engine {
class AssetManager;
class TextureAsset {
private:
	FPair<FUInt, FUInt> _size {std::make_pair(0u, 0u)};
	FUInt _channels {3u};
	FUInt _pixelsArraySize {0u};
	FUInt8* _pixelsArray {nullptr};
public:
	inline FPair<FUInt, FUInt> GetSize() const {return _size;};
	inline FUInt GetChannels() const {return _channels;};
	inline FUInt8* GetPixelArray() const {return _pixelsArray;};
private:
	friend class AssetManager;
	TextureAsset() = delete;
	explicit TextureAsset(FAssetFileContext data);
	~TextureAsset() {
		delete[] _pixelsArray;
	}
};
}
#endif // ENGINE_TEXTURE_ASSET_INCLUDED