#ifndef ENGINE_ASSET_INCLUDED
#define ENGINE_ASSET_INCLUDED
#include <utility.hpp>

namespace Engine {

class Asset {
protected:
    /*
        The Asset class deals directly with absolute path. Through the abstraction of AssetManger class, the user
        is able to get the file with a relative path
    */
    FString _fileAbsolutePath;
public:
    inline FString GetFileAbsolutePath() const {return _fileAbsolutePath;}
public:
    /*
        Load the file specified by the string (file absolute path) into the memory.
        Return whether the loading is successful.
        If a file currently in load, then close it and load the new file.
    */
    virtual bool Load(FString) = 0;
    virtual void Unload() = 0;
};

enum class EAssetType {
    Image,
    Audio
};

}

#endif