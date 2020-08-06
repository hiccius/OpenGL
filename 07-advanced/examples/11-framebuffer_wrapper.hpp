#ifndef FRAMEBUFFER_WRAPPER_HPP
#define FRAMEBUFFER_WRAPPER_HPP

#include "shaderprogram.ipp"
#include "vertexbufferobject.ipp"
#include "renderbufferobject.hpp"
#include "vertexdatahandler.hpp"
#include "texture.hpp"

class CWindow;

class CFramebufferWrapper
{
public:
    CFramebufferWrapper(int aWidth, int aHeight);
    void Bind();
    void Draw(CWindow& aWindow, int aWidth, int aHeight);

private:
    CShaderProgram      _screenShader;
    CVertexBufferObject _vboQuad;
    CVertexDataHandler  _quadData;
    CFramebuffer        _framebuffer;
    CTextureBuffer      _textureBuffer;
    CRenderbufferObject _rbo;
    CFramebuffer        _intermediateFramebuffer;
    CTextureBuffer      _colorBuffer;
};

#endif // FRAMEBUFFER_WRAPPER_HPP
