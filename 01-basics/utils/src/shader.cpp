#include "shader.hpp"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include "helpers.hpp"


std::map<CShader::Type, std::pair<std::string_view, int>> CShader::TypeCodes
{
    { Type::VertexShader,   { "VERTEX",   GL_VERTEX_SHADER   } },
    { Type::FragmentShader, { "FRAGMENT", GL_FRAGMENT_SHADER } }
};

CShader::CShader(Type aType, std::string_view aSourceCode) noexcept
    : _type{aType}, _sourceCode{aSourceCode}
{}

CShader::CShader(const std::filesystem::path& aSourceFileName)
{
    _type = GetTypeFromExtension(aSourceFileName.extension());

    try
    {
        auto shadersFolder = std::filesystem::current_path() / "01-basics" / "shaders";
        if (!std::filesystem::exists(shadersFolder))
        {
            throw OpenGLException("SHADER::FOLDER '" + shadersFolder.string() + "' DOESN'T EXIST");
        }

        auto sourceFilePath = shadersFolder / aSourceFileName;
        if (!std::filesystem::exists(sourceFilePath))
        {
            throw OpenGLException("SHADER::FILE '" + std::filesystem::absolute(sourceFilePath).string() +
                                  "' DOESN'T EXIST");
        }

        ReadSourceCode(sourceFilePath);
    }
    catch (const std::filesystem::filesystem_error& exc)
    {
        throw OpenGLException(std::string{"SHADER::ERROR ACCESSING FILE: "} + exc.what());
    }
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

        throw OpenGLException{"SHADER::" + std::string(TypeCodes[_type].first) +
                              "::COMPILATION_FAILED\n" + infoLog};
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
        throw OpenGLException{"SHADER::UNSUPPORTED SHADER TYPE: " + aExtension.string()};
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
            throw OpenGLException("SHADER::NO CONTENT FOUND IN '" + aSourceCodePath.string() + "'");
        }
    }
    catch (const std::fstream::failure& exc)
    {
        throw OpenGLException(std::string{"SHADER::ERROR READING FILE: "} + exc.what());
    }

    _sourceCode = _sourceCodeContent;
}
