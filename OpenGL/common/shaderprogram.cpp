#include "shaderprogram.h"

#include <fstream>
#include <sstream>

CShaderProgram::CShaderProgram() noexcept : _id{ glCreateProgram() } {};


void CShaderProgram::AttachShadersFromFile(CStringLiteral vertexShader, CStringLiteral fragmentShader)
{
    std::stringstream vertexShaderCode, fragmentShaderCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexShader);
        fragmentShaderFile.open(fragmentShader);

        vertexShaderCode << vertexShaderFile.rdbuf();
        fragmentShaderCode << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();
    }
    catch (const std::fstream::failure& exception)
    {
        throw OpenGLException(std::string("FILE_NOT_SUCCESFULLY_READ: ") + exception.what());
    }

    AttachNewShader(GL_VERTEX_SHADER, vertexShaderCode.str().c_str());
    AttachNewShader(GL_FRAGMENT_SHADER, fragmentShaderCode.str().c_str());
    Link();
}


template <typename TString>
GLuint CShaderProgram::AttachNewShader(GLenum shaderType, TString sourceCode)
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

template GLuint CShaderProgram::AttachNewShader(GLenum shaderType, CStringLiteral sourceCode);
template GLuint CShaderProgram::AttachNewShader(GLenum shaderType, const char* sourceCode);

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