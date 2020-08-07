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

    CRenderbufferObject(Type aType, unsigned int aSamples = 1);
    ~CRenderbufferObject() noexcept;

    CRenderbufferObject(const CRenderbufferObject& aOther) = delete;

    void SetUp(int aWidth, int aHeight);
    virtual void Attach() noexcept override final;

private:
    const unsigned int  _samples;
    unsigned int        _id;
    const Type          _type;

    unsigned int GetInternalFormat() const;
    unsigned int GetAttachmentType() const;
};

#endif // RENDERBUFFEROBJECT_HPP
