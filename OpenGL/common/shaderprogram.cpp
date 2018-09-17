#include "shaderprogram.h"


CShaderProgram::CShaderProgram() noexcept : _id{ glCreateProgram() } {};


GLuint CShaderProgram::AttachNewShader(GLenum shaderType, CStringLiteral sourceCode)
{
    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &sourceCode, nullptr);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (success)
    {
        _shaderIds.push_back(shaderId);
        return shaderId;
    }
    else
    {
        constexpr uint32_t infoLogSize{ 512 };
        char infoLog[infoLogSize];
        glGetShaderInfoLog(shaderId, infoLogSize, nullptr, infoLog);
        throw OpenGLException{ "COMPILATION_FAILED\n" + std::string(infoLog) };
    }
}


void CShaderProgram::AttachCompiledShader(GLuint shaderId)
{
    _compiledShaderIds.push_back(shaderId);
}


void CShaderProgram::Link()
{
    for (const auto& shaderId : _shaderIds)
    {
        glAttachShader(_id, shaderId);
    }
    for (const auto& shaderId : _compiledShaderIds)
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
        _compiledShaderIds.clear();
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


GLint CShaderProgram::GetUniformLocation(const std::string& name) const
{
    GLint location = glGetUniformLocation(_id, name.c_str());
    if (location != -1)
    {
        return location;
    }
    else
    {
        throw OpenGLException("Location of \"" + name + "\" not found");
    }
}