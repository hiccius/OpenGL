#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <filesystem>

class CTexture
{
public:
    enum class Type
    {
        Specular, Diffuse
    };

    CTexture(Type aType) noexcept;
    ~CTexture() noexcept;

    CTexture(CTexture&& aOther) noexcept;
    CTexture(const CTexture& aOther) = delete;

    void GenerateTexture(const std::filesystem::path& aTextureFile);
    void ActivateAndBind(int aTextureUnitIndex) const noexcept;
    Type GetType() const noexcept;

private:
    int GetImageFormat(int aColorChannels) const;

    void SetWrappingMode(int aMode) noexcept;
    void SetMinifyFilteringMode(int aMode) noexcept;
    void SetMagnifyFilteringMode(int aMode) noexcept;

    unsigned int    _id;
    Type            _type;
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
