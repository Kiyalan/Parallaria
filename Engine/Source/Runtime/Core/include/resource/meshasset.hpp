#ifndef ENGINE_MESHASSET_INCLUDED
#define ENGINE_MESHASSET_INCLUDED
#include <resource/asset.hpp>

namespace Engine {

struct FVertexAttribute {
    FReal32 position[3];
    FReal32 texCoord[2];
};

class MeshAsset :public Asset {
private:
    FVertexAttribute* _vertexAttributeArray = nullptr;
    FUInt32* _indexArray = nullptr;
    FUInt _vertexCount = 0;
public:
    /* Use carefully in the graphics pipeline because this is a naked pointer. */
    inline FVertexAttribute* GetVertexAttributeArray() const {return _vertexAttributeArray;}
    inline FUInt32* GetIndexArray() const {return _indexArray;}
    inline FUInt GetVertexCount() const {return _vertexCount;}
public:
    MeshAsset(){};
    ~MeshAsset();
    bool Load(FString) override;
    void Unload() override;
};

}

#endif
