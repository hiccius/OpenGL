#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include "helpers.hpp"

CTextureBase::CTextureBase() noexcept
{
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
}

CTextureBase::~CTextureBase() noexcept
{
    if (_id != 0)
    {
        glDeleteTextures(1, &_id);
        _id = 0;
    }
}

CTextureBase::CTextureBase(CTextureBase&& aOther) noexcept
{
    _id = aOther._id;
    aOther._id = 0;
}

void CTextureBase::SetMinifyFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, aMode);
}

void CTextureBase::SetMagnifyFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, aMode);
}

void CTextureBase::ActivateAndBind(int aTextureUnitIndex) const noexcept
{
    glActiveTexture(GL_TEXTURE0 + aTextureUnitIndex);
    glBindTexture(GL_TEXTURE_2D, _id);
}

CTexture::CTexture(Type aType) noexcept
    : _type{aType}
{}

void CTexture::SetWrappingMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, aMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, aMode);
}

void CTexture::GenerateTexture(const std::filesystem::path& aTextureFile)
{
    try
    {
        auto resourceFilePath = GetFullPath("resources" / aTextureFile);

        int width, height, colorChannels;
        stbi_set_flip_vertically_on_load(true);
#ifdef _WIN32
        const char* resourceFilePathCStr{resourceFilePath.string().c_str()};
#else
        const char* resourceFilePathCStr{resourceFilePath.c_str()};
#endif // _WIN32
        auto* data = reinterpret_cast<std::byte*>(stbi_load(resourceFilePathCStr, &width, &height, &colorChannels, 0));
        if (data)
        {
            int format = GetImageFormat(colorChannels);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            SetWrappingMode(format == GL_RGBA ? WrappingMode::ClampedEdge : WrappingMode::Repeat);
            SetMinifyFilteringMode(FilteringMode::LinearMipmapLinear);
            SetMagnifyFilteringMode(FilteringMode::Linear);

            stbi_image_free(data);
        }
        else
        {
            throw OpenGLException{"IMAGE_LOAD", "Failed to load texture from " + resourceFilePath.string()};
        }
    }
    catch (const OpenGLException& exc)
    {
        throw OpenGLException{"TEXTURE_GENERATE" + exc.GetContext(), exc.GetError()};
    }
}

CTexture::Type CTexture::GetType() const noexcept
{
    return _type;
}

int CTexture::GetImageFormat(int aColorChannels) const
{
    switch(aColorChannels)
    {
    case 1:
        return GL_RED;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        throw OpenGLException{"IMAGE_TYPE", std::to_string(aColorChannels) + " color channels are not supported"};
    }
}

void CTextureBuffer::GenerateTexture(int aWidth, int aHeight)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, aWidth, aHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    SetMinifyFilteringMode(FilteringMode::Linear);
    SetMagnifyFilteringMode(FilteringMode::Linear);
}

void CTextureBuffer::Attach() noexcept
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _id, 0);
}
