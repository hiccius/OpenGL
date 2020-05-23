#ifndef TEXTUREHANDLER_HPP
#define TEXTUREHANDLER_HPP

#include <glad/glad.h>
#include <filesystem>

class CTextureHandler
{
public:
    CTextureHandler() noexcept;
    ~CTextureHandler() noexcept;

    void SetWrappingMode(int aMode) noexcept;
    void SetFilteringMode(int aMode) noexcept;

    void GenerateTexture(const std::filesystem::path& aTextureFile);
    void BindTexture();

private:

    unsigned int _id;
};

namespace WrappingMode
{
    static constexpr int Repeat = GL_REPEAT;
}

namespace FilteringMode
{
    static constexpr int Linear = GL_LINEAR;
}

#endif // TEXTUREHANDLER_HPP
