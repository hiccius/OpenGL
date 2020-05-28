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

void CTexture::SetFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, aMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, aMode);
}

void CTexture::GenerateTexture(const std::filesystem::path& aTextureFile)
{
    try
    {
        auto resourceFilePath = GetFullPath("resources" / aTextureFile);

        int width, height, colorChannels;
        stbi_set_flip_vertically_on_load(true);
        auto* data = reinterpret_cast<std::byte*>(stbi_load(resourceFilePath.c_str(), &width, &height, &colorChannels, 0));
        if (data)
        {
            int format = GetImageFormat(aTextureFile.extension());

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
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

int CTexture::GetImageFormat(const std::filesystem::path& aExtension) const
{
    if (aExtension == ".jpg")
    {
        return GL_RGB;
    }
    else if (aExtension == ".png")
    {
        return GL_RGBA;
    }
    else
    {
        throw OpenGLException{"IMAGE_TYPE", "Unsupported image type " + aExtension.string()};
    }
}
