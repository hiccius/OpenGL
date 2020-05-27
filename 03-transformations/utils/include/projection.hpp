#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "matrix.hpp"

class CPerspective : public CMatrix
{
public:
    CPerspective(float aFoV, float aAspect, float aNear, float aFar, bool aDegrees = false) noexcept;
};

#endif // PROJECTION_HPP
