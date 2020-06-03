#include "matrix.hpp"

#include <glm/gtc/matrix_transform.hpp>

CMatrix::CMatrix(glm::mat4&& aMatrix) noexcept
    : _matrix{std::move(aMatrix)}
{}

void CMatrix::Translate(float aX, float aY, float aZ) noexcept
{
    _matrix = glm::translate(_matrix, glm::vec3{aX, aY, aZ});
}

void CMatrix::Rotate(float aAngle, float aX, float aY, float aZ, bool aDegrees) noexcept
{
    _matrix = glm::rotate(_matrix, aDegrees ? glm::radians(aAngle) : aAngle, glm::vec3{aX, aY, aZ});
}

void CMatrix::Scale(float aX, float aY, float aZ) noexcept
{
    _matrix = glm::scale(_matrix, glm::vec3{aX, aY, aZ});
}

const float* CMatrix::GetAddress() const noexcept
{
    return &_matrix[0][0];
}
