#include <glad/glad.h>
#include <GL/gl.h>
#include <graphic/shader.hpp>
#include <graphic/renderable.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {

Shader::Shader(){
    
}

Shader::~Shader(){
    Destroy();
}

/*
    Load the source into a shader (searching in the folder of the final executive main.exe) and compile the shader.
    Cause an error if the file loading or compilation fails.
*/
bool Shader::LoadShaderSource(EShaderType shaderType, FString source){
    PRINT_LOG("Shader at ", source, "begins to load.");
    // Load the file as a string
    std::ifstream file {source};
    if (!file.good()) {
        PRINT_ERROR("Shader source file failed to open.");
        return 0;
    }
    const std::string fileString {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    const char *fileCString = fileString.c_str();
    PRINT_LOG(fileCString);
    // Create a shader and source the shader
    FUInt currentShader;
    switch (shaderType) {
        case EShaderType::VertexShader:
            currentShader = _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
            break;
        case EShaderType::FragmentShader:
            currentShader = _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    glShaderSource(currentShader, 1, &fileCString, nullptr);
    // Compile the shader
    glCompileShader(currentShader);
    FInt success;
    glGetShaderiv(currentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        FInt logLength;
        glGetShaderiv(currentShader, GL_INFO_LOG_LENGTH, &logLength);
        char* infoLog = new char[logLength];
        glGetShaderInfoLog(currentShader, logLength, &logLength, infoLog);
        PRINT_ERROR("Shader compilation failed.");
        PRINT_ERROR(infoLog);
        delete[] infoLog;
        return 0;
    }
    PRINT_LOG("Shader compilation suceeded.");
    return 1;
}

bool Shader::Initialize(){
    PRINT_LOG("Shader begins initialization.");
    // Create the shader program
    _shaderProgramId = glCreateProgram();
    // Combing the vertexShader and fragmentShader into the shaderProgram (including assotiate the output of vertexShader to the input of fragmentShader)
    if (!_vertexShaderId) {
        PRINT_ERROR("Vertex shader unloaded");
        return 0;
    }
    glAttachShader(_shaderProgramId, _vertexShaderId);
    if (!_fragmentShaderId) {
        PRINT_ERROR("Fragment shader unloaded");
        return 0;
    }
    glAttachShader(_shaderProgramId, _fragmentShaderId);
    glLinkProgram(_shaderProgramId);
    glUseProgram(_shaderProgramId);
    if (!glGetError()) {
        PRINT_LOG("Shader initialization completed.");
        return 1;
    } else {
        PRINT_ERROR("Shader initialization failed.");
        return 0;
    }
}

void Shader::BindShaderInput(std::initializer_list<ShaderInput> list) const {
    glUseProgram(_shaderProgramId);
    for (auto &val : list) {
        FInt AttributeLocation = glGetAttribLocation(_shaderProgramId, val.name.c_str());
        glEnableVertexAttribArray(AttributeLocation);
        // Only support FReal32 type, no normailized
        glVertexAttribPointer(AttributeLocation, val.size, GL_FLOAT, false, val.stride * sizeof(FVertexAttributeDataType), (void *)(val.offset * sizeof(FVertexAttributeDataType)));
    }
}

void Shader::BindShaderOutput(std::initializer_list<ShaderOutput> list) const {
    glUseProgram(_shaderProgramId);
    for (auto &val : list) {
        // Associate the output of fragmentShader with the currently binded framebuffer (the default one) color attachment 0.
        glBindFragDataLocation(_shaderProgramId, val.attachment, val.name.c_str());
    }
}

void Shader::Enable() const {
    glUseProgram(_shaderProgramId);
}

void Shader::Destroy(){
    FUInt currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, (FInt32 *)&currentProgram);
    if (currentProgram == _shaderProgramId)
        glUseProgram(0);
    if (_shaderProgramId)
        glDeleteProgram(_shaderProgramId);
    if (_vertexShaderId)
        glDeleteShader(_vertexShaderId);
    if (_fragmentShaderId)
        glDeleteShader(_fragmentShaderId);
}

}