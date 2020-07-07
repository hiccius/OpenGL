#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <map>
#include <filesystem>

class CShader
{
public:
    enum class Type {VertexShader, FragmentShader};
    static std::map<Type, std::pair<std::string_view, int>> TypeCodes;

    CShader(Type aType, std::string_view aSourceCode) noexcept;
    CShader(const std::filesystem::path& aSourceFileName);
    CShader(CShader&& aOther) noexcept;
    ~CShader() noexcept;

    void Compile();
    void Delete() noexcept;
    int GetId() const noexcept;

private:
    Type GetTypeFromExtension(const std::filesystem::path& aExtension) const;
    void ReadSourceCode(const std::filesystem::path& aSourceCodePath);

    Type             _type;
    unsigned int     _shaderId{0};
    std::string      _sourceCodeContent;
    std::string_view _sourceCode;
};

#endif // SHADER_HPP
