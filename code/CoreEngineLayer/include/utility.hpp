#ifndef ENGINE_UTILITY_INCLUDED
#define ENGINE_UTILITY_INCLUDED

#include <env.hpp>

#include <string>
using FString = std::string;

// use FReal64
struct FRealVector2D { 
    FReal64 x, y;
    FRealVector2D(FReal64 ix = .0, FReal64 iy = .0) :x{ix}, y{iy} {;}
};

#include <vector>
template<class T>
using FDynamicArray = std::vector<T>;

#endif
