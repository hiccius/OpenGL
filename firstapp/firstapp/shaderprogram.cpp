#include "shaderprogram.h"


CShaderProgram::CShaderProgram() noexcept : _id{ glCreateProgram() } {};


void CShaderProgram::AttachNewShader(GLenum shaderType, CStringLiteral sourceCode)
{
    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &sourceCode, nullptr);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (success)
    {
        _shaderIds.push_back(shaderId);
    }
    else
    {
        constexpr uint32_t infoLogSize{ 512 };
        char infoLog[infoLogSize];
        glGetShaderInfoLog(shaderId, infoLogSize, nullptr, infoLog);
        throw OpenGLException{ "COMPILATION_FAILED\n" + std::string(infoLog) };
    }
}


void CShaderProgram::Link()
{
    for (const auto& shaderId : _shaderIds)
    {
        glAttachShader(_id, shaderId);
    }
    glLinkProgram(_id);

    GLint success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (success)
    {
        for (const auto& shaderId : _shaderIds)
        {
            glDeleteShader(shaderId);
        }
        _shaderIds.clear();
    }
    else
    {
        constexpr uint32_t infoLogSize{ 512 };
        char infoLog[infoLogSize];
        glGetProgramInfoLog(_id, infoLogSize, nullptr, infoLog);
        throw OpenGLException{ "LINK_FAILED\n" + std::string(infoLog) };
    }
}


void CShaderProgram::Use()
{
    glUseProgram(_id);
}