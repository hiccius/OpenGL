#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "shader.hpp"


class CShaderProgram
{
public:
    CShaderProgram() noexcept;
    ~CShaderProgram() noexcept;

    void Link(const CShader& aVertexShader, const CShader& aFragmentShader);
    void Use() const noexcept;

private:
    unsigned int _id;
};

#endif // SHADERPROGRAM_HPP
