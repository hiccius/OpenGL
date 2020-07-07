#include "shaderprogram.hpp"

#include <glad/glad.h>
#include <string>

template<typename T, typename>
void CShaderProgram::SetUniform(const std::string& aName, T aValue)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform1i(uniformLocation, aValue);
}
