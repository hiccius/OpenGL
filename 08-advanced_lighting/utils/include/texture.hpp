#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <filesystem>
#include "framebuffer.hpp"

class CTextureBase
{
public:
    CTextureBase(bool aMultisample = false) noexcept;
    ~CTextureBase() noexcept;

    CTextureBase(CTextureBase&& aOther) noexcept;
    CTextureBase(const CTextureBase& aOther) = delete;

    void ActivateAndBind(int aTextureUnitIndex) const noexcept;

protected:
    void SetMinifyFilteringMode(int aMode) noexcept;
    void SetMagnifyFilteringMode(int aMode) noexcept;
    void SetWrappingMode(int aMode) noexcept;

    const int       _target;
    unsigned int    _id;
};


class CTexture : public CTextureBase
{
public:
    enum class Type
    {
        Specular, Diffuse
    };

    CTexture(Type aType) noexcept;

    void GenerateTexture(const std::filesystem::path& aTextureFile);
    Type GetType() const noexcept;

private:
    int GetImageFormat(int aColorChannels) const;

    Type _type;
};


class CTextureBuffer : public CTextureBase, public CFramebufferAttachment
{
public:
    CTextureBuffer(unsigned int aSamples = 1);
    void GenerateTexture(int aWidth, int aHeight);

    virtual void Attach() noexcept override final;

private:
    const unsigned int _samples;
};

namespace WrappingMode
{
    static constexpr int Repeat         = GL_REPEAT;
    static constexpr int Mirror         = GL_MIRRORED_REPEAT;
    static constexpr int ClampedEdge    = GL_CLAMP_TO_EDGE;
}

namespace FilteringMode
{
    static constexpr int Linear             = GL_LINEAR;
    static constexpr int LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR;
    static constexpr int Nearest            = GL_NEAREST;
}

#endif // TEXTURE_HPP
