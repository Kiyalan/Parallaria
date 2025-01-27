#ifndef ENGINE_SHADER_INCLUDED
#define ENGINE_SHADER_INCLUDED
#include <utility.hpp>
#include <initializer_list>

/*
    Potential reconstruction
*/

namespace Engine {

enum class EShaderType {
    VertexShader,
    FragmentShader
};

struct ShaderOutput {
    FString name;
    FUInt attachment;
    ShaderOutput(FString iName, FUInt iAttachment) :name{iName}, attachment{iAttachment} {;}
};

struct ShaderInput {
    FString name;
    FUInt size, stride, offset;
    ShaderInput(FString iName, FUInt iSize, FUInt iStride, FUInt iOffset) :name{iName}, size{iSize}, stride{iStride}, offset{iOffset} {;}
};

class Shader {
private:
    FUInt _vertexShaderId = 0;
    FUInt _fragmentShaderId = 0;
    FUInt _shaderProgramId = 0;
public:
    Shader();
    ~Shader();
    /*
        Load shader from source. Only support vertex shader and fragment shader.
        Currently it is not united with asset loading. In the near future, shader may be considered a resource.
    */
    bool LoadShaderSource(EShaderType, FString);
    /*
        The data binding between the input of fragment shader and the output of vertex shader is done the linking the shader program
    */
    bool Initialize();
    void Destroy();
    /*
        Bind the output of the shader (fragment shader) to a framebuffer color attachment (now default framebuffer, default color attachment 0).
        The layer structure is: shaderoutput -> attachment of framebuffer -> screen.
        The structure means that before the binding, the shader program and the framebuffer must be the OpenGL binded one. When switching between shader programs, it is necessary to rebind the shader output.
    */
    void BindShaderOutput(std::initializer_list<ShaderOutput>) const;
    /*
        Bind vertex attribute data to the input of the shader (vertex shader).
        The layer structure is: data -> shaderinput.
        The structure means that before the binding, the data (vertex buffer, texture) and the shader must be the OpenGL binded one.
        The texture input data binding interface is to be provided.
    */
    void BindShaderInput(std::initializer_list<ShaderInput>) const;
    void Enable() const;
    
};



}


#endif