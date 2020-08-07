#include "shaderprogram.hpp"

#include <string>
#include <glad/glad.h>
#include "helpers.hpp"

template<typename T, typename>
void CShaderProgram::SetUniform(const std::string& aName, T aValue)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform1i(uniformLocation, aValue);
}

template<std::size_t N>
void CShaderProgram::Link(const CShader (&aShaders)[N])
{
    if (_id == 0)
    {
        throw OpenGLException{"SHADER_PROGRAM", "Not initialised"};
    }

    for (std::size_t i = 0; i < N; ++i)
    {
        AttachShader(aShaders[i]);
    }

    glLinkProgram(_id);

    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);

    if (!success)
    {
        std::string infoLog{};
        int infoLogSize;

        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogSize);
        infoLog.resize(infoLogSize);

        glGetProgramInfoLog(_id, infoLogSize, nullptr, infoLog.data());

        throw OpenGLException{"SHADER_PROGRAM", "Linking failed:\n" + infoLog};
    }
}
