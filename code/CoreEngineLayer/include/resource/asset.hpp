#ifndef ENGINE_ASSET_INCLUDED
#define ENGINE_ASSET_INCLUDED
#include <utility.hpp>
#include <memory>

namespace Engine {

class Asset {
private:
    FString _fileRelativePath;
public:
    // file relative path and folder form the complete absolute path
    static FString assetFolder;

    FString GetFileRelativePath() const {return _fileRelativePath;};
    /*
        Load the file specified by the string(file relative path) into the memory.
        Return whether the loading is successful.
        If a file currently in load, then close it and load the new file.
    */
    virtual bool Load(FString) = 0;
    virtual void Unload(FString) = 0;
    // The mapping of file relative path to Asset pointer.
    static FHashTable<FString, std::shared_ptr<Asset> > assetTable;
};

}

#endif