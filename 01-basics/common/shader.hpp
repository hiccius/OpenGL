#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <map>


class CShader
{
public:
    enum class Type {VertexShader, FragmentShader};
    static std::map<Type, std::pair<std::string_view, int>> TypeCodes;

    CShader(Type, std::string_view sourceCode) noexcept;
    ~CShader() noexcept;

    void Compile();
    void Delete() noexcept;
    int GetId() const noexcept;

private:
    Type             _type{};
    unsigned int     _shaderId{0};
    std::string_view _sourceCode{};
};

#endif // SHADER_HPP
