#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

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
    void Bind() noexcept;
    void ClearColor(float aX, float aY, float aZ, float aW) noexcept;

private:
    unsigned int _id;
};

class CFramebufferAttachment
{
public:
    virtual void Attach() noexcept = 0;
};

#endif // FRAMEBUFFER
