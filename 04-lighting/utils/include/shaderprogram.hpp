#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glm/glm.hpp>
#include "shader.hpp"

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
    void SetUniform(const std::string& aName, float aX, float aY, float aZ);
    void SetUniform(const std::string& aName, float aX, float aY, float aZ, float aW);
    void SetUniform(const std::string& aName, float aValue);
    void SetUniform(const std::string& aName, int aValue);
    void SetUniform(const std::string& aName, const CMatrix& aValue);

    void Use() const;

private:
    int GetUniformLocation(const std::string& aName) const;

    unsigned int _id;
    mutable std::map<std::string, int> _uniformsCache;
};

#endif // SHADERPROGRAM_HPP
