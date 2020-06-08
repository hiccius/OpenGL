#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include "helpers.hpp"

CTexture::CTexture() noexcept
{
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
}

CTexture::~CTexture() noexcept
{
    if (_id != 0)
    {
        glDeleteTextures(1, &_id);
        _id = 0;
        _textureUnitIndex = 0;
    }
}

CTexture::CTexture(CTexture&& aOther) noexcept
{
    _id = aOther._id;
    _textureUnitIndex = aOther._textureUnitIndex;

    aOther._id = 0;
    aOther._textureUnitIndex = 0;
}

void CTexture::SetWrappingMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, aMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, aMode);
}

void CTexture::SetMinifyFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, aMode);
}

void CTexture::SetMagnifyFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, aMode);
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

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            SetWrappingMode(WrappingMode::Repeat);
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

void CTexture::SetTextureUnitIndex(int aTextureUnitIndex) noexcept
{
    _textureUnitIndex = aTextureUnitIndex;
}

void CTexture::ActivateAndBind() const noexcept
{
    glActiveTexture(GL_TEXTURE0 + _textureUnitIndex);
    glBindTexture(GL_TEXTURE_2D, _id);
}

int CTexture::GetImageFormat(int aColorChannels) const
{
    switch(aColorChannels)
    {
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        throw OpenGLException{"IMAGE_TYPE", std::to_string(aColorChannels) + " color channels are not supported"};
    }
}
