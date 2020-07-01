#ifndef RENDERBUFFEROBJECT_HPP
#define RENDERBUFFEROBJECT_HPP

#include "framebuffer.hpp"

class CRenderbufferObject : public CFramebufferAttachment
{
public:
    enum class Type
    {
        Stencil, Depth, DepthAndStencil
    };

    CRenderbufferObject(Type aType) noexcept;
    ~CRenderbufferObject() noexcept;

    CRenderbufferObject(const CRenderbufferObject& aOther) = delete;

    void SetUp(int aWidth, int aHeight);
    virtual void Attach() noexcept override final;

private:
    unsigned int    _id;
    Type            _type;

    unsigned int GetInternalFormat() const;
    unsigned int GetAttachmentType() const;
};

#endif // RENDERBUFFEROBJECT_HPP
