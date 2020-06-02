#ifndef MATRIXDERIVED_HPP
#define MATRIXDERIVED_HPP

#include <glm/gtc/matrix_transform.hpp>
#include "matrix.hpp"

class CPerspectiveMatrix : public CMatrix
{
public:
    CPerspectiveMatrix(float aFoV, float aAspect, float aNear, float aFar,
                       bool aDegrees = false) noexcept
        : CMatrix{glm::perspective(aDegrees ? glm::radians(aFoV) : aFoV, aAspect, aNear, aFar)}
    {}
};

class CViewMatrix : public CMatrix
{
public:
    CViewMatrix(const glm::vec3& aPosition, const glm::vec3& aDirection,
                const glm::vec3& aUp = glm::vec3(0.0f, 1.0f, 0.0f)) noexcept
        : CMatrix{glm::lookAt(aPosition, aDirection, aUp)}
    {}
};

#endif // MATRIXDERIVED_HPP
