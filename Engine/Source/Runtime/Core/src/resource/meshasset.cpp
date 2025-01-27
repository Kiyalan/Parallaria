#include <resource/meshasset.hpp>
#include <fstream>

namespace Engine {

MeshAsset::~MeshAsset() {
    if (_vertexAttributeArray)
        Unload();
}

bool MeshAsset::Load(FString absPath) {
    std::ifstream file(absPath, std::ios::binary);
    if (!file.is_open()) {
        PRINT_ERROR("MeshAsset loading failure at", absPath);
        return 0;
    }
    
}

void MeshAsset::Unload() {
    if (!_vertexAttributeArray) {
        PRINT_ERROR("You cannot unload MeshAsset before loading it.");
        return;
    }
    delete[] _vertexAttributeArray;
    _vertexAttributeArray = nullptr;
    delete[] _indexArray;
    _indexArray = nullptr;
    _vertexCount = 0;
}

}