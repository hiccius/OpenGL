#ifndef GLADHELPERS_HPP
#define GLADHELPERS_HPP

#include <glad/glad.h>   // needs to be included always before GLFW
#include <GLFW/glfw3.h>

#include "helpers.hpp"


void LoadGLAD()
{
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw OpenGLException("Failed to initialize GLAD");
    }
}

#endif // GLADHELPERS_HPP
