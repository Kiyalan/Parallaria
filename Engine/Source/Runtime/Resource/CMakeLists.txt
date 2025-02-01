add_library(ResourceLayer STATIC
    Source/AssetManager/AssetManager.cpp
    Source/Asset/TextureAsset.cpp
)

target_include_directories(ResourceLayer PUBLIC "Include")

target_link_libraries(ResourceLayer PRIVATE RapidJSONLib)
target_link_libraries(ResourceLayer PRIVATE STBLib)
target_link_libraries(ResourceLayer PRIVATE GLILib)
target_link_libraries(ResourceLayer PRIVATE OpenGLLib)
target_link_libraries(ResourceLayer PRIVATE CoreLayer)

add_executable(SerializableTest "Source/Serialization/SerializableTest.cpp")
target_link_libraries(SerializableTest PRIVATE ResourceLayer)
target_link_libraries(SerializableTest PRIVATE CoreLayer)