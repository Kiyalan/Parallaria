add_library(FunctionLayer STATIC
    "Source/Context/EngineContext.cpp"
)
target_include_directories(FunctionLayer PUBLIC "Include")
target_link_libraries(FunctionLayer PRIVATE CoreLayer ResourceLayer)