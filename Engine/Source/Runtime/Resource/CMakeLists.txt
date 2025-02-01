add_library(ResourceLayer STATIC
    Source/AssetManager/AssetManager.cpp
    Source/Asset/TextureAsset.cpp
    Source/Asset/MeshAsset.cpp
)

target_include_directories(ResourceLayer PUBLIC "Include")

target_link_libraries(ResourceLayer PRIVATE RapidJSONLib)
target_link_libraries(ResourceLayer PRIVATE STBLib)
target_link_libraries(ResourceLayer PRIVATE GLILib)
target_link_libraries(ResourceLayer PRIVATE OpenGLLib)
target_link_libraries(ResourceLayer PRIVATE CoreLayer)
target_link_libraries(ResourceLayer PRIVATE AssimpLib)

add_executable(SerializableTest "Source/Serialization/SerializableTest.cpp")
target_link_libraries(SerializableTest PRIVATE ResourceLayer)
target_link_libraries(SerializableTest PRIVATE CoreLayer)

if(WIN32) # platform check, only windows
    add_custom_command(TARGET SerializableTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SerializableTest> $<TARGET_FILE_DIR:SerializableTest>
        # COMMAND_EXPAND_LISTS
        VERBATIM 
    )
endif()