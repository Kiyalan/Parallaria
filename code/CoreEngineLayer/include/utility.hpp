#ifndef ENGINE_UTILITY_INCLUDED
#define ENGINE_UTILITY_INCLUDED

#include <env.hpp>

// Debug on / off
#define ENGINE_DEBUG_ON
#define ENGINE_RUNTIME_DEBUG_ON
// Log function for debugging
#include <iostream>
inline void _printLog(){std::cout << std::endl;}
template <typename T, typename... Args>
inline void _printLog(T&& first, Args&&... args){
    std::cout << first << " ";
    _printLog(std::forward<Args>(args)...);
}
inline void _printError(){std::cerr << std::endl;}
template <typename T, typename... Args>
inline void _printError(T&& first, Args&&... args){
    std::cerr << first << " ";
    _printLog(std::forward<Args>(args)...);
}
#define PRINT_ERROR(...) _printError(__VA_ARGS__)
#ifdef ENGINE_DEBUG_ON // common log
    #define PRINT_LOG(...) _printLog(__VA_ARGS__)
#else
    #define PRINT_LOG(...) 666
#endif
#ifdef ENGINE_RUNTIME_DEBUG_ON
    #define PRINT_RUNTIME_LOG(...) _printLog(__VA_ARGS__)
#else
    #define PRINT_RUNTIME_LOG(...) 777
#endif


// use FReal64
struct FRealVector2D { 
    FReal64 x, y;
    FRealVector2D(FReal64 ix = .0, FReal64 iy = .0) :x{ix}, y{iy} {;}
};

struct FIntVector2D {
    FInt32 x, y;
    FIntVector2D(FInt32 ix = 0, FInt32 iy = 0) :x{ix}, y{iy} {;}
};

// enum class ERectangleStyle {

// };
// struct FRectangle {
//     FInt left, right, bottom, top;

// }

#include <string>
using FString = std::string;

#include <vector>
template<class Type>
using FDynamicArray = std::vector<Type>;

#include <array>
template<class Type, FUInt length>
using FStaticArray = std::array<Type, length>;

#include <queue>
template<class Type>
using FQueue = std::queue<Type>;

#include <unordered_map>
template<class KeyType, class ValueType>
using FHashTable = std::unordered_map<KeyType, ValueType>;

#include <memory>
template<typename Type>
using FSharedPointer = std::shared_ptr<Type>;

#endif
