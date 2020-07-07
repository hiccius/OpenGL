#include "renderbufferobject.hpp"

#include "glad/glad.h"
#include "helpers.hpp"

CRenderbufferObject::CRenderbufferObject(Type aType) noexcept
    : _type{aType}
{
    glGenRenderbuffers(1, &_id);
    glBindRenderbuffer(GL_RENDERBUFFER, _id);
}

CRenderbufferObject::~CRenderbufferObject() noexcept
{
    glDeleteRenderbuffers(1, &_id);
}

void CRenderbufferObject::SetUp(int aWidth, int aHeight)
{
    glRenderbufferStorage(GL_RENDERBUFFER, GetInternalFormat(), aWidth, aHeight);
}

void CRenderbufferObject::Attach() noexcept
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GetAttachmentType(), GL_RENDERBUFFER, _id);
}

unsigned int CRenderbufferObject::GetInternalFormat() const
{
    switch(_type)
    {
    case Type::DepthAndStencil:
        return GL_DEPTH24_STENCIL8;
    default:
        throw OpenGLException("RENDERBUFFER", "Type not supported");
    }
}

unsigned int CRenderbufferObject::GetAttachmentType() const
{
    switch(_type)
    {
    case Type::DepthAndStencil:
        return GL_DEPTH_STENCIL_ATTACHMENT;
    default:
        throw OpenGLException("RENDERBUFFER", "Type not supported");
    }
}
