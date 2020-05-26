#include "matrix.hpp"

#include <glm/gtc/matrix_transform.hpp>

CMatrix::CMatrix() noexcept
    : _matrix{1.0f}
{}

void CMatrix::Translate(float aX, float aY, float aZ) noexcept
{
    _matrix = glm::translate(_matrix, glm::vec3{aX, aY, aZ});
}

void CMatrix::Rotate(float aAngle, Axis aRotationAxis, bool aDegrees) noexcept
{
    _matrix = glm::rotate(_matrix, aDegrees ? glm::radians(aAngle) : aAngle, GetUnitVector(aRotationAxis));
}

void CMatrix::Scale(float aX, float aY, float aZ) noexcept
{
    _matrix = glm::scale(_matrix, glm::vec3{aX, aY, aZ});
}

const float* CMatrix::GetAddress() const noexcept
{
    return &_matrix[0][0];
}

glm::vec3 CMatrix::GetUnitVector(Axis aAxis) const noexcept
{
    switch (aAxis)
    {
        case Axis::X: return glm::vec3{1.0f, 0.0f, 0.0f};
        case Axis::Y: return glm::vec3{0.0f, 1.0f, 0.0f};
        case Axis::Z: return glm::vec3{0.0f, 0.0f, 1.0f};
    }
}
