#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "glad/glad.h"

class CFramebufferAttachment;

class CFramebuffer
{
public:
    CFramebuffer() noexcept;
    ~CFramebuffer() noexcept;

    CFramebuffer(CFramebuffer&& aOther) noexcept;
    CFramebuffer(const CFramebuffer& aOther) = delete;

    void Attach(CFramebufferAttachment* aAttachment);
    bool IsComplete() noexcept;

    static void BindDefault() noexcept;
    void Blit(CFramebuffer& aDestination, int aWidth, int aHeight) noexcept;

    enum class Target
    {
        Read        = GL_READ_FRAMEBUFFER,
        Draw        = GL_DRAW_FRAMEBUFFER,
        ReadAndDraw = GL_FRAMEBUFFER
    };

    void Bind(Target aTarget = Target::ReadAndDraw) noexcept;

private:
    unsigned int _id;
};

class CFramebufferAttachment
{
public:
    virtual void Attach() noexcept = 0;
};

#endif // FRAMEBUFFER
