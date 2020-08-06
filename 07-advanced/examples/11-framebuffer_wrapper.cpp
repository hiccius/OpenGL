#include "11-framebuffer_wrapper.hpp"

#include "window.hpp"
#include "helpers.hpp"

CFramebufferWrapper::CFramebufferWrapper(int aWidth, int aHeight)
    : _screenShader{CShaderProgram::Build("11-quad.vert", "11-quad.frag")},
      _textureBuffer{4}, _rbo{CRenderbufferObject::Type::DepthAndStencil, 4}
{
    auto screenShader{CShaderProgram::Build("11-quad.vert", "11-quad.frag")};
    screenShader.Use();
    screenShader.SetUniform("screenTexture", 0);

    constexpr float quadVertices[] =
    {
        // positions   // texture coordinates
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    _vboQuad.AddVertexData(quadVertices);
    _quadData.AddVertexBufferObject(&_vboQuad);
    _quadData.AddAttribute(2, 4, 0, false);
    _quadData.AddAttribute(2, 4, 2, false);

    _framebuffer.Bind();
    _textureBuffer.GenerateTexture(aWidth, aHeight);
    _framebuffer.Attach(&_textureBuffer);

    _rbo.SetUp(aWidth, aHeight);
    _framebuffer.Attach(&_rbo);

    if (!_framebuffer.IsComplete())
    {
        throw OpenGLException{"FRAMEBUFFER", "Main framebuffer is not complete"};
    }

    _intermediateFramebuffer.Bind();
    _colorBuffer.GenerateTexture(aWidth, aHeight);
    _intermediateFramebuffer.Attach(&_colorBuffer);

    if (!_intermediateFramebuffer.IsComplete())
    {
        throw OpenGLException{"FRAMEBUFFER", "Intermediate framebuffer is not complete"};
    }
}

void CFramebufferWrapper::Bind()
{
    _framebuffer.Bind();
}

void CFramebufferWrapper::Draw(CWindow& aWindow, int aWidth, int aHeight)
{
    _framebuffer.Blit(_intermediateFramebuffer, aWidth, aHeight);
    CFramebuffer::BindDefault();
    aWindow.SetDepthTest(false);
    aWindow.ClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    _screenShader.Use();
    _colorBuffer.ActivateAndBind(0);
    _quadData.DrawArrays(6);
}
