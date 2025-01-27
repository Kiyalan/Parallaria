add_library(SDL3 STATIC IMPORTED)
set_target_properties(SDL3 PROPERTIES 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3/SDL3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3/SDL3.a"
)
add_library(SDL3_mixer STATIC IMPORTED)
set_target_properties(SDL3_mixer PROPERTIES 
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3_mixer/SDL3_mixer.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL3_mixer/SDL3_mixer.a"
)
add_library(SDL3Lib STATIC placeholder.cpp)
# target_include_directories(SDL3Lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(SDL3Lib PUBLIC SDL3)
target_link_libraries(SDL3Lib PUBLIC SDL3_mixer)
if(WIN32)
    target_link_libraries(SDL3Lib PUBLIC winmm imm32 setupapi version)
endif()