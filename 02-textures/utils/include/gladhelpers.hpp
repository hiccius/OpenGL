#ifndef GLADHELPERS_HPP
#define GLADHELPERS_HPP

#include <glad/glad.h>   // needs to be included always before GLFW
#include <GLFW/glfw3.h>

#include "helpers.hpp"


void LoadGLAD()
{
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw OpenGLException{"GLAD_LOADER", "Failed to initialize GLAD"};
    }
}

void FillShape(bool fill)
{
    glPolygonMode(GL_FRONT_AND_BACK, fill ? GL_FILL : GL_LINE);
}

#endif // GLADHELPERS_HPP
