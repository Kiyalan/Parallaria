#pragma once
#define ENGINE_ASSERT_ON
#ifdef ENGINE_ASSERT_ON
    void _DynamicAssertLog(const char* expr, const char* msg, const char* file, unsigned line);
    #define DYNAMIC_ASSERT(expr, msg) ((expr) || (_DynamicAssertLog(#expr, msg, __FILE__, (unsigned)(__LINE__)), 0))
    #define STATIC_ASSERT(expr, msg) static_assert(expr, msg)
#else
    #define DYNAMIC_ASSERT ((void)0)
    #define STATIC_ASSERT ((void)0)
#endif
