#include "framebuffer.hpp"

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

void CFramebuffer::Bind(CFramebuffer::Target aTarget) noexcept
{
    glBindFramebuffer(static_cast<GLenum>(aTarget), _id);
}

void CFramebuffer::Blit(CFramebuffer& aDestination, int aWidth, int aHeight) noexcept
{
    Bind(Target::Read);
    aDestination.Bind(Target::Draw);
    glBlitFramebuffer(0, 0, aWidth, aHeight, 0, 0, aWidth, aHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
