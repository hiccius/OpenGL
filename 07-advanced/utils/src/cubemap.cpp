#include "cubemap.hpp"

#include <array>
#include <stb_image.h>
#include <glad/glad.h>
#include "helpers.hpp"
#include "texture.hpp"

CCubemap::CCubemap() noexcept
{
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}

CCubemap::~CCubemap() noexcept
{
    if (_id != 0)
    {
        glDeleteTextures(1, &_id);
    }
}

CCubemap::CCubemap(CCubemap&& aOther) noexcept
{
    _id = aOther._id;
    aOther._id = 0;
}

void CCubemap::GenerateTexture(const std::filesystem::path& aTextureFolder)
{
    auto cubemapPath = GetFullPath("resources" / aTextureFolder);
    auto textureTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
    for (const auto& face : {"right.jpg",  "left.jpg",  "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"})
    {
        int width, height, channels;
        auto facePath = cubemapPath / face;
        stbi_set_flip_vertically_on_load(false);
        auto* data = stbi_load(facePath.c_str(), &width, &height, &channels, 0);
        if (data)
        {
            glTexImage2D(textureTarget++, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);

            SetMinifyFilteringMode(FilteringMode::Linear);
            SetMagnifyFilteringMode(FilteringMode::Linear);
            SetWrappingMode(WrappingMode::ClampedEdge);
        }
        else
        {
            throw OpenGLException{"IMAGE_LOAD", "Failed to load texture from " + facePath.string()};
        }
    }
}

void CCubemap::Bind() const noexcept
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}

void CCubemap::SetMinifyFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, aMode);
}

void CCubemap::SetMagnifyFilteringMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, aMode);
}

void CCubemap::SetWrappingMode(int aMode) noexcept
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, aMode);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, aMode);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, aMode);
}
