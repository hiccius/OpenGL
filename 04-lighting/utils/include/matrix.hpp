#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <glm/glm.hpp>
#include "customtypes.hpp"

class CMatrix
{
public:
    constexpr CMatrix() noexcept : _matrix{1.0f} {}

    void Translate(float aX, float aY, float aZ) noexcept;
    void Translate(const RawFloatVector3& aVector) noexcept;
    void Rotate(float aAngle, float aX, float aY, float aZ, bool aDegrees = false) noexcept;
    void Scale(float aFactor) noexcept;
    void Scale(float aX, float aY, float aZ) noexcept;

    const float* GetAddress() const noexcept;

protected:
    CMatrix(glm::mat4&& aMatrix) noexcept;

    glm::mat4 _matrix;
};

#endif // TRANSFORMATIONMATRIX_HPP
