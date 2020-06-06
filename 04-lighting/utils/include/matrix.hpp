#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <glm/glm.hpp>
#include "customtypes.hpp"

class CMatrix
{
public:
    constexpr CMatrix() noexcept : _matrix{1.0f} {}

    CMatrix& Translate(float aX, float aY, float aZ) noexcept;
    CMatrix& Translate(const RawFloatVector3& aVector) noexcept;
    CMatrix& Rotate(float aAngle, float aX, float aY, float aZ, bool aDegrees = false) noexcept;
    CMatrix& Scale(float aFactor) noexcept;
    CMatrix& Scale(float aX, float aY, float aZ) noexcept;

    const float* GetAddress() const noexcept;

protected:
    CMatrix(glm::mat4&& aMatrix) noexcept;

    glm::mat4 _matrix;
};

#endif // TRANSFORMATIONMATRIX_HPP
