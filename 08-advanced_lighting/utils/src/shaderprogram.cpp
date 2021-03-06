#include "shaderprogram.ipp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "matrix.hpp"

CShaderProgram CShaderProgram::Build(std::string_view aVertexShader, std::string_view aFragmentShader)
{
    CShaderProgram shaderProgram;

    CShader vertexShader{aVertexShader};
    CShader fragmentShader{aFragmentShader};

    vertexShader.Compile();
    fragmentShader.Compile();

    shaderProgram.Link({std::move(vertexShader), std::move(fragmentShader)});

    return shaderProgram;
}

CShaderProgram CShaderProgram::Build(std::string_view aVertexShader, std::string_view aGeometryShader, std::string_view aFragmentShader)
{
    CShaderProgram shaderProgram;

    CShader vertexShader{aVertexShader};
    CShader fragmentShader{aFragmentShader};
    CShader geometryShader{aGeometryShader};

    vertexShader.Compile();
    geometryShader.Compile();
    fragmentShader.Compile();

    shaderProgram.Link({std::move(vertexShader), std::move(geometryShader), std::move(fragmentShader)});

    return shaderProgram;
}

CShaderProgram::CShaderProgram() noexcept
    : _id{glCreateProgram()}
{}

CShaderProgram::~CShaderProgram() noexcept
{
    if (_id)
    {
        glDeleteProgram(_id);
    }
}

CShaderProgram::CShaderProgram(CShaderProgram&& aOther) noexcept
    : _id{aOther._id}, _uniformsCache{aOther._uniformsCache}
{
    aOther._id = 0;
}

void CShaderProgram::SetUniform(const std::string& aName, float aX, float aY)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform2f(uniformLocation, aX, aY);
}

void CShaderProgram::SetUniform(const std::string& aName, float aX, float aY, float aZ)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform3f(uniformLocation, aX, aY, aZ);
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

void CShaderProgram::SetUniform(const std::string& aName, const CMatrix& aValue)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, aValue.GetAddress());
}

void CShaderProgram::SetUniform(const std::string& aName, const RawFloatVector3& aVector)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform3fv(uniformLocation, 1, &aVector[0]);
}

void CShaderProgram::SetUniform(const std::string& aName, const std::array<float, 3>& aArray)
{
    int uniformLocation = GetUniformLocation(aName);
    glUniform3fv(uniformLocation, 1, aArray.data());
}

int CShaderProgram::GetUniformLocation(const std::string& aName) const
{
    if (_id == 0)
    {
        throw OpenGLException{"SHADER_PROGRAM", "Not initialised"};
    }

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

void CShaderProgram::Use() const
{
    if (_id == 0)
    {
        throw OpenGLException{"SHADER_PROGRAM", "Not initialised"};
    }

    glUseProgram(_id);
}

void CShaderProgram::SetBindingPoint(std::string_view aBlockName, unsigned int aBindingPoint)
{
    glUniformBlockBinding(_id, GetUniformBlockIndex(aBlockName), aBindingPoint);
}

unsigned int CShaderProgram::GetUniformBlockIndex(std::string_view aBlockName) const
{
    auto index = glGetUniformBlockIndex(_id, aBlockName.data());
    if (index == GL_INVALID_INDEX)
    {
        throw OpenGLException{"SHADER_PROGRAM", std::string{aBlockName} + " is not a valid uniform block"};
    }
    else
    {
        return index;
    }
}

void CShaderProgram::AttachShader(const CShader& aShader)
{
    if (aShader.GetId() == 0)
    {
        throw OpenGLException{"SHADER_PROGRAM", aShader.GetTypeName() + " shader needs to be compiled"};
    }
    else
    {
        glAttachShader(_id, aShader.GetId());
    }
}
