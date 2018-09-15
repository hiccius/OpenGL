#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "helpers.h"


class CShaderProgram
{
public:
    CShaderProgram() noexcept;

    void AttachNewShader(GLenum shaderType, CStringLiteral sourceCode);
    void Link();

    void Use();

private:
    GLuint              _id;
    std::vector<GLuint> _shaderIds;
};