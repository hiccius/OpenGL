#include "shader.hpp"

#include <glad/glad.h>
#include "helpers.hpp"


std::map<CShader::Type, std::pair<std::string_view, int>> CShader::TypeCodes
{
    { Type::VertexShader,   { "VERTEX",   GL_VERTEX_SHADER   } },
    { Type::FragmentShader, { "FRAGMENT", GL_FRAGMENT_SHADER } }
};

CShader::CShader(Type type, std::string_view sourceCode) noexcept
    : _type{type}, _sourceCode{sourceCode}
{}

CShader::~CShader() noexcept
{
    Delete();
}

void CShader::Compile()
{
    unsigned int shaderId = glCreateShader(TypeCodes[_type].second);
    const char* sourceCodeString = _sourceCode.data();
    glShaderSource(shaderId, 1, &sourceCodeString, nullptr);
    glCompileShader(shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::string infoLog{};
        int infoLogSize;

        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogSize);
        infoLog.resize(infoLogSize);

        glGetShaderInfoLog(shaderId, infoLogSize, nullptr, infoLog.data());
        glDeleteShader(shaderId);

        throw OpenGLException("SHADER::" + std::string(TypeCodes[_type].first) +
                              "::COMPILATION_FAILED\n" + infoLog);
    }

    _shaderId = shaderId;
}

void CShader::Delete() noexcept
{
    if (_shaderId != 0)
    {
        glDeleteShader(_shaderId);
        _shaderId = 0;
    }
}

int CShader::GetId() const noexcept
{
    return _shaderId;
}
