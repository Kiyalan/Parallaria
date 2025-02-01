#include <fstream>
#include <iostream>

#include <Resource/Asset/TextureAsset.hpp>


template <typename T>
using has_increment = decltype(std::declval<T&>()++, void());

int main(){
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

    // for (int i = 0; i < tex2.GetSize().first; ++i) {
    //     for (int j = 0; j < tex2.GetSize().second; ++j) {
    //         if (tex2.GetPixelArray()[])
    //     }
    // }
    return 0;
}
