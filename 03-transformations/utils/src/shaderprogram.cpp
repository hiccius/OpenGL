#include "shaderprogram.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "helpers.hpp"
#include "matrix.hpp"


CShaderProgram::CShaderProgram() noexcept
    : _id{glCreateProgram()}
{}

CShaderProgram::~CShaderProgram() noexcept
{
    glDeleteProgram(_id);
}

void CShaderProgram::Link(const CShader& aVertexShader, const CShader& aFragmentShader)
{
    if (aVertexShader.GetId() == 0)
    {
        throw OpenGLException{"SHADER_PROGRAM", "Vertex shader needs to be compiled"};
    }

    if (aFragmentShader.GetId() == 0)
    {
        throw OpenGLException{"SHADER_PROGRAM", "Fragment shader needs to be compiled"};
    }

    glAttachShader(_id, aVertexShader.GetId());
    glAttachShader(_id, aFragmentShader.GetId());
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

void CShaderProgram::SetUniform(const std::string& aName, float aX, float aY, float aZ, float aW)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform4f(uniformLocation, aX, aY, aZ, aW);
}

void CShaderProgram::SetUniform(const std::string& aName, float aValue)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform1f(uniformLocation, aValue);
}

void CShaderProgram::SetUniform(const std::string& aName, int aValue)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform1i(uniformLocation, aValue);
}

void CShaderProgram::SetUniform(const std::string& aName, const CMatrix& aValue)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, aValue.GetAddress());
}

int CShaderProgram::GetUniformLocation(const std::string& aName) const
{
    if (auto cached{_uniformsCache.find(aName)}; cached != _uniformsCache.end())
    {
        return cached->second;
    }

    int uniformLocation = glGetUniformLocation(_id, aName.c_str());
    if (uniformLocation < 0)
    {
        throw OpenGLException{"SHADER_PROGRAM", "Location of uniform '" + aName + "' not found"};
    }

    _uniformsCache[aName] = uniformLocation;
    return uniformLocation;
}

void CShaderProgram::Use() const noexcept
{
    glUseProgram(_id);
}
