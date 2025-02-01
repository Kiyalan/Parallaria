#include <iostream>

#include <Development/Assert/Assert.hpp>

void _DynamicAssertLog(const char* expr, const char* msg, const char* file, unsigned line){
    std::cerr << "Assertion failed: " << expr << " at " << file << " line " << line << " : " << msg << std::endl;
    std::abort();
}