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
template<class Type>
using FDynamicArray = std::vector<Type>;

#include <array>
template<class Type, FUInt length>
using FStaticArray = std::array<Type, length>;

#include <unordered_map>
template<class KeyType, class ValueType>
using FHashTable = std::unordered_map<KeyType, ValueType>;

#endif
