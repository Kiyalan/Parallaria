#ifndef ENGINE_IMAGEASSET_INCLUDED
#define ENGINE_IMAGEASSET_INCLUDED
#include <resource/asset.hpp>
namespace Engine {

class ImageAsset :public Asset {
private:
    unsigned char* _content = nullptr;  
    FIntVector2D _size;
    FInt _channels;
public:
    inline const unsigned char* GetContent() const {return _content;}
    inline FIntVector2D GetSize() const {return _size;}
    inline FInt GetChannels() const {return _channels;}
public:
    bool Load(FString) override;
    void Unload() override;
};

}
#endif