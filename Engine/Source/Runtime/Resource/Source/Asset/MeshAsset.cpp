#include <iostream>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <Resource/Asset/MeshAsset.hpp>

namespace Engine {

bool MeshAsset::LoadFromFile(std::filesystem::path path){
    if (!std::filesystem::exists(path)) 
        return PRINT_ERROR("TextureAsset::LoadFromFile: File does not exist.", path), false;
    std::string extension = path.extension().string();
    if (extension == ".obj") {
        Assimp::Importer importer;
        // Restriction: Assuming the input winding order is counter-clockwise
        const aiScene* scene = importer.ReadFile(path.string().c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            return PRINT_ERROR("MeshAsset::LoadFromFile: File could not be loaded.", path), false;
        _vertexCount = _indexArraySize = 0;
        // Restriction: Load all vertex into one whole mesh
        for (FUInt i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
            _vertexCount += mesh->mNumVertices;
            _indexArraySize += mesh->mNumFaces * 3;
            DYNAMIC_ASSERT(mesh->HasPositions(), "MeshAsset::LoadFromFile: Mesh does not have positions.");
            // Restriction: Only consider the first texture
            DYNAMIC_ASSERT(mesh->HasTextureCoords(0), "MeshAsset::LoadFromFile: Mesh does not have texture coordinates.");
        }
        DYNAMIC_ASSERT(_vertexArray == nullptr && _indexArray == nullptr, "MeshAsset::LoadFromFile: Mesh is already loaded.");
        _vertexArraySize = _vertexCount * VertexAttributeWidth;
        _vertexArray = new FReal[_vertexArraySize];
        _indexArray = new FUInt[_indexArraySize];
        for (FUInt i = 0, vertexAttribSum = 0, indexSum = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
            for (FUInt j = 0; j < mesh->mNumVertices; ++j) {
                _vertexArray[vertexAttribSum    ] = mesh->mVertices[j].x;
                _vertexArray[vertexAttribSum + 1] = mesh->mVertices[j].y;
                _vertexArray[vertexAttribSum + 2] = mesh->mVertices[j].z;
                _vertexArray[vertexAttribSum + 3] = mesh->mTextureCoords[0][j].x;
                _vertexArray[vertexAttribSum + 4] = mesh->mTextureCoords[0][j].y;
                // Restriction: Do not load vertex colors
                _vertexArray[vertexAttribSum + 5] = 1.f;
                _vertexArray[vertexAttribSum + 6] = 1.f;
                _vertexArray[vertexAttribSum + 7] = 1.f;
                vertexAttribSum += VertexAttributeWidth;
            }
            for (FUInt j = 0; j < mesh->mNumFaces; ++j) {
                const aiFace* face = &mesh->mFaces[j];  
                _indexArray[indexSum + 0] = face->mIndices[0];
                _indexArray[indexSum + 1] = face->mIndices[1];
                _indexArray[indexSum + 2] = face->mIndices[2];
                indexSum += 3;
            }
        }
    } else
        return PRINT_ERROR("MeshAsset::LoadFromFile: Unsupported file format.", path), false;
    return true;
}

}