#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "shader.hpp"


class CShaderProgram
{
public:
    CShaderProgram() noexcept;
    ~CShaderProgram() noexcept;

    void Link(const CShader& aVertexShader, const CShader& aFragmentShader);
    void SetUniform(const std::string& aName, float aX, float aY, float aZ, float aW);
    void SetUniform(const std::string& aName, float aValue);
    void Use() const noexcept;

private:
    int GetUniformLocation(const std::string& aName) const;

    unsigned int _id;
};

#endif // SHADERPROGRAM_HPP
