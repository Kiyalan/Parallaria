#ifndef ENGINE_ASSET_INCLUDED
#define ENGINE_ASSET_INCLUDED
#include <utility.hpp>

namespace Engine {

class Asset {
public:
    /*
        Load the file specified by the string into the memory.
        Return whether the loading is successful.
        If a file currently in load, then close it and load the new file.
    */
    virtual bool Load(FString) = 0;
};

}
#endif