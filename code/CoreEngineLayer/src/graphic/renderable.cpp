#include <graphic/renderable.hpp>
#include <glad/glad.h>
#include <GL/gl.h>
#include <resource/assetmanager.hpp>
#include <resource/imageasset.hpp>
#include <graphic/shader.hpp>

namespace Engine {

RenderableImage2D::RenderableImage2D(){

}

RenderableImage2D::~RenderableImage2D(){
    if (_initialized)
        Destroy();
}

void RenderableImage2D::SetImageAsset(FString path){
    _imageAsset = std::static_pointer_cast<const ImageAsset>(AssetManager::RequestAsset(EAssetType::Image, path));
}

void RenderableImage2D::SetShader(FSharedPointer<const Shader> shader){
    _shader = shader;
}

bool RenderableImage2D::Initialize(){
    if (_initialized) {
        PRINT_RUNTIME_LOG("Renderable re-initialization begins.");
        Destroy();
    } else {
        PRINT_RUNTIME_LOG("Renderable initialization begins.");
    }
    if (!_imageAsset) {
        PRINT_ERROR("ImageAsset unset.");
        return 0;
    }
    if (!_shader) {
        PRINT_ERROR("Shader unset.");
        return 0;
    }
    // Switch to correct shader
    _shader->Enable();
    // Use VAOs (vertex array objects) to store VBO binding and configurations.
    glGenVertexArrays(1, &_vertexArrayId);
    glBindVertexArray(_vertexArrayId);
    // Create and bind (make active) VBO, upload data and bind the input of shader program
    FInt storeType = GL_DYNAMIC_DRAW;
    glGenBuffers(1, &_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(FVertexAttributeDataType) * _vertexAttributeArray.size(), _vertexAttributeArray.data(), storeType);
    _shader->BindShaderInput({ShaderInput("iPosition", 3, _vertexAttributeSize, 0), ShaderInput("iTexCoord", 2, _vertexAttributeSize, 3)});
    // Create and bind EBO, upload data
    glGenBuffers(1, &_elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(FIndexDataType) * _indexArray.size(), _indexArray.data(), storeType);
    // Unbind VAO
    glBindVertexArray(0);
    // Create and bind texture buffer, configure texture setting, upload data and unbind
    glGenTextures(1, &_textureBufferId);
    glActiveTexture(GL_TEXTURE0); // Single image drawing only requires one texture unit
    glBindTexture(GL_TEXTURE_2D, _textureBufferId);
    FInt filterType = GL_LINEAR, wrapType = GL_REPEAT;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);
    FInt detailNumberLevel = 0; // base image, higher for mipmaps
    FInt internalFormat, externalFormat;
    switch (_imageAsset->GetChannels()) {
        case 4: internalFormat = externalFormat = GL_RGBA; break;
        case 3: internalFormat = externalFormat = GL_RGB; break;
        default: internalFormat = GL_DEPTH_COMPONENT; externalFormat = GL_RED; break;
    }
    glTexImage2D(GL_TEXTURE_2D, detailNumberLevel, internalFormat, _imageAsset->GetSize().x, _imageAsset->GetSize().y, 0, externalFormat, GL_UNSIGNED_BYTE, _imageAsset->GetContent());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (glGetError()) {
        PRINT_ERROR("Renderable initialization failed.");
        return 0;
    }
    PRINT_RUNTIME_LOG("Renderable initialization succeeded.");
    _initialized = 1;
    return 1;
}

void RenderableImage2D::Destroy(){
    if (_initialized) {
        glDeleteBuffers(1, &_elementBufferId);
        glDeleteBuffers(1, &_vertexBufferId);
        glDeleteTextures(1, &_textureBufferId);
        glDeleteVertexArrays(1, &_vertexArrayId);
        _initialized = 0;
    } else {
        PRINT_ERROR("You cannot destroy a renderable before initialzed.");
    }
}

void RenderableImage2D::Render(){
    // Switching over different shaders
    if (!_initialized) {
        PRINT_ERROR("You cannot use a renderable before initialized.");
        return;
    }
    // Activate shader
    _shader->Enable();
    _shader->BindShaderOutput({ShaderOutput("fColor", 0)});
    // Rebind textures and vertices
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureBufferId);
    glUniform1i(0, 0);
    glBindVertexArray(_vertexArrayId);
    // Update data in buffers
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(FVertexAttributeDataType) * _vertexAttributeArray.size(), _vertexAttributeArray.data());
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(FIndexDataType) * _indexArray.size(), _indexArray.data());
    // Draw
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
    // Unbind textures and vertices
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

}