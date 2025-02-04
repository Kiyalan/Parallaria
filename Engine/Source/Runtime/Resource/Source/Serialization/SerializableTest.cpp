#include <fstream>
#include <iostream>

#include <env.hpp>
#include <Resource/Asset/TextureAsset.hpp>
#include <Resource/Asset/MeshAsset.hpp>

int main(){
    /*
      TextureAsset Test

    Engine::TextureAsset tex1;
    if (!tex1.LoadFromFile("D:/GuaGua/Game/Parallaria/Engine/Resource/PatrickStar.jpg"))
        return -1;
    std::cout << tex1.GetSize().first << ", " << tex1.GetSize().second << std::endl;
    std::cout << tex1.GetFormat() << std::endl;
    tex1.Serialize<1>("D:/GuaGua/Game/Parallaria/Engine/Resource/PatrickStar.asset");

    Engine::TextureAsset tex2;
    tex2.Serialize<0>("D:/GuaGua/Game/Parallaria/Engine/Resource/PatrickStar.asset");
    std::cout << tex2.GetSize().first << ", " << tex2.GetSize().second << std::endl;
    std::cout << tex2.GetFormat() << std::endl;

    for (int i = 0; i < tex2.GetSize().first; ++i) {
        for (int j = 0; j < tex2.GetSize().second; ++j) {
            if (tex2.GetPixelArray()[i][j] != tex1.GetPixelArray()[i][j]) {
                std::cout << tex2.GetPixelArray()[i][j] << ", " << tex1.GetPixelArray()[i][j] << std::endl;
                return -1;
            }
        }
    }
    */
    Engine::MeshAsset mesh1;
    if (!mesh1.LoadFromFile("D:/GuaGua/Game/Parallaria/Engine/Resource/Square.obj"))
        return std::cout << "mesh1load failed" << std::endl, -1;
    std::cout << mesh1.GetVertexCount() << ", " << mesh1.GetIndexArraySize() << std::endl;
    for (FUInt i = 0; i < mesh1.GetVertexCount(); ++i) {
        for (FUInt j = 0; j < Engine::MeshAsset::VertexAttributeWidth; ++j)
            std::cout << mesh1.GetVertexArray()[i * Engine::MeshAsset::VertexAttributeWidth + j] << ", ";
        std::cout << std::endl;
    }
    for (FUInt i = 0; i < mesh1.GetIndexArraySize(); ++i)
        std::cout << mesh1.GetIndexArray()[i] << ", ";
    std::cout << std::endl;
    if (mesh1.Serialize<1>("D:/GuaGua/Game/Parallaria/Engine/Resource/Square.asset"))
        std::cout << "s Success" << std::endl;

    Engine::MeshAsset mesh2;
    if (mesh2.Serialize<0>("D:/GuaGua/Game/Parallaria/Engine/Resource/Square.asset"))
        std::cout << "ds Success" << std::endl;
    std::cout << mesh2.GetVertexCount() << ", " << mesh2.GetIndexArraySize() << std::endl;
    for (FUInt i = 0; i < mesh2.GetVertexCount(); ++i) {
        for (FUInt j = 0; j < Engine::MeshAsset::VertexAttributeWidth; ++j)
            std::cout << mesh2.GetVertexArray()[i * Engine::MeshAsset::VertexAttributeWidth + j] << ", ";
        std::cout << std::endl;
    }
    for (FUInt i = 0; i < mesh2.GetIndexArraySize(); ++i)
        std::cout << mesh2.GetIndexArray()[i] << ", ";
    std::cout << std::endl;
    return 0;
}
