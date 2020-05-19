#include "shaderprogram.hpp"

#include <glad/glad.h>
#include "helpers.hpp"


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
        throw OpenGLException{"SHADER::VERTEX::NEEDS_TO_BE_COMPILED"};
    }

    if (aFragmentShader.GetId() == 0)
    {
        throw OpenGLException{"SHADER::FRAGMENT::NEEDS_TO_BE_COMPILED"};
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

        throw OpenGLException{"SHADER::PROGRAM::LINKING_FAILED\n" + infoLog};
    }
}

void CShaderProgram::SetUniform(const std::string& aName, float aX, float aY, float aZ, float aW)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform4f(uniformLocation, aX, aY, aZ, aW);
}

int CShaderProgram::GetUniformLocation(const std::string& aName) const
{
    int uniformLocation = glGetUniformLocation(_id, aName.c_str());

    if (uniformLocation < 0)
    {
        throw OpenGLException{"SHADER::PROGRAM::UNIFORM_LOCATION_NOT_FOUND: '" + aName + "'"};
    }

    return uniformLocation;
}

void CShaderProgram::Use() const noexcept
{
    glUseProgram(_id);
}
