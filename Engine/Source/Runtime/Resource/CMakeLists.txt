add_library(ResourceLayer STATIC
    Source/AssetManager/AssetManager.cpp
    Source/Asset/TextureAsset.cpp
)

target_include_directories(ResourceLayer PUBLIC "Include")

target_link_libraries(ResourceLayer PRIVATE RapidJSONLib)
target_link_libraries(ResourceLayer PRIVATE CoreLayer)