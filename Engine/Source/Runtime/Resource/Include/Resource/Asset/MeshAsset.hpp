#ifndef ENGINE_MESH_ASSET_INCLUDED
#define ENGINE_MESH_ASSET_INCLUDED
#include <filesystem>

#include <env.hpp>
#include <Resource/Serialization/Serializable.hpp>
#include <Development/Pattern/GSProperty.hpp>


namespace Engine {
class AssetManager;
/**
 * This asset represent a single mesh object as a whole.
 */
class MeshAsset {
    // Developing Exception: Must be used after loading or deserializing from a file
    READONLY_PROPERTY(FUInt, v, V, ertexCount, 0)
    READONLY_PROPERTY(FUInt, v, V, ertexArraySize, 0)
    READONLY_PROPERTY(FReal*, v, V, ertexArray, nullptr)
    /**
     * Follow the OpenGL enum GL_TRIANGLES, i.e. each three indices defines a triangle
     */
    READONLY_PROPERTY(FUInt, i, I, ndexArraySize, 0)
    READONLY_PROPERTY(FUInt*, i, I, ndexArray, nullptr)
public:
    constexpr static FUInt VertexAttributeWidth = 8;

    SERIALIZATION_START()
		SERIALIZATION_ADD_FUNDAMENTAL(_vertexCount)
        SERIALIZATION_ADD_ARRAY(_vertexArraySize, _vertexArray)
		SERIALIZATION_ADD_ARRAY(_indexArraySize, _indexArray)
	SERIALIZATION_END()
// Temporary: public for testing
public:
	friend class AssetManager;
	MeshAsset() = default;
	~MeshAsset() {
        delete[] _vertexArray;
        delete[] _indexArray;
    }
	/* 
	Depracated: JSON constructor
	explicit TextureAsset(FAssetFileContext data);
	*/
// Temporary: public for testing
public:
	bool LoadFromFile(std::filesystem::path);
};

}
#endif // ENGINE_TEXTURE_ASSET_INCLUDED