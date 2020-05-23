#include "texturehandler.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

#include "helpers.hpp"


CTextureHandler::CTextureHandler() noexcept
{
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
}

CTextureHandler::~CTextureHandler() noexcept
{
    glDeleteTextures(1, &_id);
}

void CTextureHandler::SetWrappingMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, aMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, aMode);
}

void CTextureHandler::SetFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, aMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, aMode);
}

void CTextureHandler::GenerateTexture(const std::filesystem::path& aTextureFile)
{
    try
    {
        auto resourceFilePath = GetFullPath("resources" / aTextureFile);

        int width, height, colorChannels;
        auto* data = reinterpret_cast<std::byte*>(stbi_load(resourceFilePath.c_str(), &width, &height, &colorChannels, 0));
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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

void CTextureHandler::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, _id);
}
