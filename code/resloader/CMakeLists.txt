set(srcfile placeholder.cpp)
set(incdir stb)
add_library(resourceLoader STATIC ${srcfile})
target_include_directories(resourceLoader PUBLIC ${incdir})