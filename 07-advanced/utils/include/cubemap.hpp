#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <filesystem>

class CCubemap
{
public:
    CCubemap() noexcept;
    ~CCubemap() noexcept;

    CCubemap(CCubemap&& aOther) noexcept;
    CCubemap(const CCubemap& aOther) = delete;

    void GenerateTexture(const std::filesystem::path& aTextureFolder);
    void Bind() const noexcept;

private:
    void SetMinifyFilteringMode(int aMode) noexcept;
    void SetMagnifyFilteringMode(int aMode) noexcept;
    void SetWrappingMode(int aMode) noexcept;

    unsigned int _id;
};

#endif // CUBEMAP_HPP
