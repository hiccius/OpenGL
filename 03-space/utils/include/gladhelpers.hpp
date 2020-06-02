#ifndef GLADHELPERS_HPP
#define GLADHELPERS_HPP

#include <glad/glad.h>
#include "helpers.hpp"

void FillShape(bool fill)
{
    glPolygonMode(GL_FRONT_AND_BACK, fill ? GL_FILL : GL_LINE);
}

#endif // GLADHELPERS_HPP
