#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glm/glm.hpp>
#include "shader.hpp"

class CMatrix;

class CShaderProgram
{
public:
    CShaderProgram() noexcept;
    ~CShaderProgram() noexcept;

    void Link(const CShader& aVertexShader, const CShader& aFragmentShader);

    template<typename T>
    void SetUniform(const std::string& aName, T aX, T aY, T aZ, T aW) = delete;
    void SetUniform(const std::string& aName, float aX, float aY, float aZ, float aW);
    template<typename T>
    void SetUniform(const std::string& aName, T aValue) = delete;
    void SetUniform(const std::string& aName, float aValue);
    void SetUniform(const std::string& aName, int aValue);
    void SetUniform(const std::string& aName, const CMatrix& aValue);

    void Use() const noexcept;

private:
    int GetUniformLocation(const std::string& aName) const;

    unsigned int _id;
    mutable std::map<std::string, int> _uniformsCache;
};

#endif // SHADERPROGRAM_HPP
