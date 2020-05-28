#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <filesystem>

class CTexture
{
public:
    CTexture() noexcept;
    ~CTexture() noexcept;

    CTexture(CTexture&& aOther) noexcept;
    CTexture(const CTexture& aOther) = delete;

    void SetWrappingMode(int aMode) noexcept;
    void SetFilteringMode(int aMode) noexcept;

    void GenerateTexture(const std::filesystem::path& aTextureFile);
    void SetTextureUnitIndex(int aTextureUnitIndex) noexcept;
    void ActivateAndBind() const noexcept;

private:
    int GetImageFormat(const std::filesystem::path& aExtension) const;

    unsigned int _id;
    unsigned int _textureUnitIndex{0};
};

namespace WrappingMode
{
    static constexpr int Repeat = GL_REPEAT;
    static constexpr int Mirror = GL_MIRRORED_REPEAT;
    static constexpr int ClampedEdge = GL_CLAMP_TO_EDGE;
}

namespace FilteringMode
{
    static constexpr int Linear = GL_LINEAR;
    static constexpr int Nearest = GL_NEAREST;
}

#endif // TEXTURE_HPP
