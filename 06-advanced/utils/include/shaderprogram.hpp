#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glm/glm.hpp>
#include <array>
#include <type_traits>
#include "shader.hpp"
#include "customtypes.hpp"

class CMatrix;

class CShaderProgram
{
public:
    static CShaderProgram Build(std::string_view aVertexShader, std::string_view aFragmentShader);

    CShaderProgram() noexcept;
    ~CShaderProgram() noexcept;
    CShaderProgram(CShaderProgram&& aOther) noexcept;

    void Link(const CShader& aVertexShader, const CShader& aFragmentShader);

    template<typename ...T>
    void SetUniform(const std::string& aName, T...) = delete;
    template<typename T,
             typename = std::enable_if_t<std::is_same_v<int, T> || std::is_same_v<bool, T>>>
    void SetUniform(const std::string& aName, T aValue);
    void SetUniform(const std::string& aName, float aX, float aY, float aZ);
    void SetUniform(const std::string& aName, float aX, float aY, float aZ, float aW);
    void SetUniform(const std::string& aName, float aValue);
    void SetUniform(const std::string& aName, const CMatrix& aValue);
    void SetUniform(const std::string& aName, const RawFloatVector3& aVector);
    void SetUniform(const std::string& aName, const std::array<float, 3>& aArray);

    void Use() const;

private:
    int GetUniformLocation(const std::string& aName) const;

    unsigned int _id;
    mutable std::map<std::string, int> _uniformsCache;
};

#endif // SHADERPROGRAM_HPP
