#ifndef ENGINE_TEXTURE_ASSET_INCLUDED
#define ENGINE_TEXTURE_ASSET_INCLUDED
#include <filesystem>
#include <utility>
#include <env.hpp>
#include <Resource/Serialization/Serializable.hpp>


namespace Engine {
class AssetManager;
class TextureAsset {
private:
	std::pair<FUInt, FUInt> _size {std::make_pair(0u, 0u)};
	// Description: The (external) format of the pixel data, using OpenGL's enum
	FUInt _format;
	FUInt _pixelsArraySize;
	FUInt8* _pixelsArray {nullptr};
public:
	// Developing Exception: Must be used after loading or deserializing from a file
	inline std::pair<FUInt, FUInt> GetSize() const {return _size;};
	inline FUInt GetFormat() const {return _format;};
	inline FUInt8* GetPixelArray() const {return _pixelsArray;};
// Temporary: public for testing
public:
	friend class AssetManager;
	TextureAsset() = default;
	~TextureAsset() {delete[] _pixelsArray;}
	/* 
	Depracated: JSON constructor
	explicit TextureAsset(FAssetFileContext data);
	*/
// Temporary: public for testing
public:
	bool LoadFromFile(std::filesystem::path);
	SERIALIZATION_START()
		SERIALIZATION_ADD_FUNDAMENTAL(_size)
		SERIALIZATION_ADD_FUNDAMENTAL(_format)
		SERIALIZATION_ADD_FUNDAMENTAL(_pixelsArraySize)
		SERIALIZATION_ADD_ARRAY(_pixelsArraySize, _pixelsArray)
	SERIALIZATION_END()
};

}
#endif // ENGINE_TEXTURE_ASSET_INCLUDED