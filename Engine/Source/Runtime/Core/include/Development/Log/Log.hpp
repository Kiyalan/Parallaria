#pragma once
#ifndef ENGINE_LOG_INCLUDED
#define ENGINE_LOG_INCLUDED
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
    _printError(std::forward<Args>(args)...);
}
#define PRINT_ERROR(...) _printError(__VA_ARGS__)
#ifdef ENGINE_DEBUG_ON // common log
    #define PRINT_LOG(...) _printLog(__VA_ARGS__)
#else
    #define PRINT_LOG(...) ((void)0)
#endif
#ifdef ENGINE_RUNTIME_DEBUG_ON
    #define PRINT_RUNTIME_LOG(...) _printLog(__VA_ARGS__)
#else
    #define PRINT_RUNTIME_LOG(...) ((void)0)
#endif

#endif