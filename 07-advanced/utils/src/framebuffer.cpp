#include "framebuffer.hpp"

#include "glad/glad.h"

CFramebuffer::CFramebuffer() noexcept
{
    glGenFramebuffers(1, &_id);
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

CFramebuffer::~CFramebuffer() noexcept
{
    if (_id != 0)
    {
        glDeleteFramebuffers(1, &_id);
    }
}

CFramebuffer::CFramebuffer(CFramebuffer&& aOther) noexcept
    : _id{aOther._id}
{
    aOther._id = 0;
}

void CFramebuffer::Attach(CFramebufferAttachment* aAttachment)
{
    aAttachment->Attach();
}

bool CFramebuffer::IsComplete() noexcept
{
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void CFramebuffer::BindDefault() noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CFramebuffer::Bind() noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}
