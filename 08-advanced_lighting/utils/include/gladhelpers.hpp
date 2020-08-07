#ifndef GLADHELPERS_HPP
#define GLADHELPERS_HPP

#include <glad/glad.h>
#include "helpers.hpp"

void FillShape(bool fill)
{
    glPolygonMode(GL_FRONT_AND_BACK, fill ? GL_FILL : GL_LINE);
}

void SetBlending(int aSourceFactor, int aDestinationFactor)
{
    glEnable(GL_BLEND);
    glBlendFunc(aSourceFactor, aDestinationFactor);
}

namespace BlendingFactor
{
    static constexpr int Alpha              = GL_SRC_ALPHA;
    static constexpr int AlphaComplement    = GL_ONE_MINUS_SRC_ALPHA;
}

#endif // GLADHELPERS_HPP
