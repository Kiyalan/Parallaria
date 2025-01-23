#ifndef ENGINE_RENDERABLE_INCLUDED
#define ENGINE_RENDERABLE_INCLUDED
#include <utility.hpp>
namespace Engine {

class Renderable {
public:
    virtual bool Initialize() = 0;
    virtual void Destroy() = 0;
    virtual void Render() = 0;
};

class RenderablePolygon2D :public Renderable {
    
};

class Shader;
class ImageAsset;
using FVertexAttributeDataType = FReal32;
using FIndexDataType = FUInt32;

class RenderableImage2D :public Renderable {
private:
    FUInt _vertexBufferId = 0;
    FUInt _textureBufferId = 0;
    FUInt _elementBufferId = 0;
    FUInt _vertexArrayId = 0;
    const static FUInt _vertexAttributeSize = 5; // 3 for iPosition and 2 for iTexCoord
    const static FUInt _vertexCount = 4;
    
    const static FUInt _triangleCount = 2;
    const static FUInt _indexCount = 3 * _triangleCount;
    FStaticArray<FIndexDataType, _indexCount> _indexArray {0, 1, 3, 3, 1, 2};
    /*
        The vertex index is designated below
        1------0
        |------|
        |------|
        2------3
    */
private:
    FSharedPointer<const ImageAsset> _imageAsset;
public:
    void SetImageAsset(FString);
    inline FSharedPointer<const ImageAsset> GetImageAsset(){return _imageAsset;}
private:
    FSharedPointer<const Shader> _shader;
public:
    void SetShader(FSharedPointer<const Shader>);
    inline FSharedPointer<const Shader> GetShader(){return _shader;}
private:
    // FRectangle _screenPos;
public:
    FStaticArray<FVertexAttributeDataType, _vertexCount * _vertexAttributeSize> _vertexAttributeArray;
public:
    RenderableImage2D();
    ~RenderableImage2D();
    bool _initialized = 0;
    bool Initialize() override;
    void Destroy() override;
    /*
        Now the rendering process is seemingly low efficient, because each renderable is assotiated with a shader; when render a renderable,
        it forces to switch to current environment that the shader needs, which might introduce extra overhead. There are a lot in common in
        the rendering process with regard to different renderables, which leaves the room for optimization of the graphic pipeline. e.g. All
        RenderableImage2D shadres the same vertex array structure. 
    */
    void Render() override;
};

}
#endif