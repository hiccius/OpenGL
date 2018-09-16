#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "helpers.h"


class CShaderProgram
{
public:
    CShaderProgram() noexcept;

    GLuint AttachNewShader(GLenum shaderType, CStringLiteral sourceCode);
    void   AttachCompiledShader(GLuint shaderId);
    void   Link();

    void Use();

private:
    GLuint              _id;
    std::vector<GLuint> _shaderIds;
    std::vector<GLuint> _compiledShaderIds;
};