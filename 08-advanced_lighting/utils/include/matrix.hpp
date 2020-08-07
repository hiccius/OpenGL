#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <glm/glm.hpp>
#include <array>
#include "customtypes.hpp"

class CMatrix
{
public:
    constexpr CMatrix() noexcept : _matrix{1.0f} {}

    CMatrix& Translate(float aX, float aY, float aZ) noexcept;
    CMatrix& Translate(const std::array<float, 3>& aArray) noexcept;
    CMatrix& Rotate(float aAngle, float aX, float aY, float aZ, bool aDegrees = false) noexcept;
    CMatrix& Scale(float aFactor) noexcept;
    CMatrix& Scale(float aX, float aY, float aZ) noexcept;

    CMatrix& Transpose() noexcept;
    CMatrix& Inverse() noexcept;

    const float* GetAddress() const noexcept;

    CMatrix operator*(const CMatrix& other) const noexcept;

    static constexpr std::size_t Size() noexcept
    {
        return sizeof(glm::mat4);
    }

protected:
    CMatrix(glm::mat4&& aMatrix) noexcept;

    glm::mat4 _matrix;
};

#endif // TRANSFORMATIONMATRIX_HPP
