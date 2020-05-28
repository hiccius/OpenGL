#include "shader.hpp"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include "helpers.hpp"


std::map<CShader::Type, std::pair<std::string_view, int>> CShader::TypeCodes
{
    { Type::VertexShader,   { "Vertex",   GL_VERTEX_SHADER   } },
    { Type::FragmentShader, { "Fragment", GL_FRAGMENT_SHADER } }
};

CShader::CShader(Type aType, std::string_view aSourceCode) noexcept
    : _type{aType}, _sourceCode{aSourceCode}
{}

CShader::CShader(const std::filesystem::path& aSourceFileName)
{
    _type = GetTypeFromExtension(aSourceFileName.extension());

    try
    {
        auto sourceFilePath = GetFullPath("shaders" / aSourceFileName);
        ReadSourceCode(sourceFilePath);
    }
    catch (const OpenGLException& exc)
    {
        throw OpenGLException{"SHADER" + exc.GetContext(), exc.GetError()};
    }
}

CShader::CShader(CShader&& aOther) noexcept
    : _type{aOther._type}, _shaderId{aOther._shaderId},
      _sourceCodeContent{aOther._sourceCodeContent}, _sourceCode{_sourceCodeContent}
{
    _shaderId = 0;
}

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

        throw OpenGLException{"SHADER_COMPILE", "Compilation of " + std::string(TypeCodes[_type].first) +
                              " shader failed:\n" + infoLog};
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

CShader::Type CShader::GetTypeFromExtension(const std::filesystem::path& aExtension) const
{
    if (aExtension == ".vert")
    {
        return Type::VertexShader;
    }
    else if (aExtension == ".frag")
    {
        return Type::FragmentShader;
    }
    else
    {
        throw OpenGLException{"", "Unsupported shader type " + aExtension.string()};
    }
}

void CShader::ReadSourceCode(const std::filesystem::path& aSourceCodePath)
{
    try
    {
        std::ifstream shaderFile;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        shaderFile.open(aSourceCodePath);

        std::stringstream stream{_sourceCodeContent};
        stream << shaderFile.rdbuf();
        _sourceCodeContent = stream.str();
        if (_sourceCodeContent.empty())
        {
            throw OpenGLException{"READ_SOURCE", "No content found in '" + aSourceCodePath.string() + "'"};
        }
    }
    catch (const std::fstream::failure& exc)
    {
        throw OpenGLException{"READ_SOURCE", + exc.what()};
    }

    _sourceCode = _sourceCodeContent;
}
