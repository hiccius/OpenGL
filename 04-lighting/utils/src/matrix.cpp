#include "matrix.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CMatrix::CMatrix(glm::mat4&& aMatrix) noexcept
    : _matrix{std::move(aMatrix)}
{}

CMatrix& CMatrix::Translate(float aX, float aY, float aZ) noexcept
{
    _matrix = glm::translate(_matrix, glm::vec3{aX, aY, aZ});
    return *this;
}

CMatrix& CMatrix::Translate(const RawFloatVector3& aVector) noexcept
{
    _matrix = glm::translate(_matrix, glm::make_vec3(aVector));
    return *this;
}

CMatrix& CMatrix::Rotate(float aAngle, float aX, float aY, float aZ, bool aDegrees) noexcept
{
    _matrix = glm::rotate(_matrix, aDegrees ? glm::radians(aAngle) : aAngle, glm::vec3{aX, aY, aZ});
    return *this;
}

CMatrix& CMatrix::Scale(float aFactor) noexcept
{
    _matrix = glm::scale(_matrix, glm::vec3{aFactor});
    return *this;
}

CMatrix& CMatrix::Scale(float aX, float aY, float aZ) noexcept
{
    _matrix = glm::scale(_matrix, glm::vec3{aX, aY, aZ});
    return *this;
}

CMatrix& CMatrix::Transpose() noexcept
{
    _matrix = glm::transpose(_matrix);
    return *this;
}

CMatrix& CMatrix::Inverse() noexcept
{
    _matrix = glm::inverse(_matrix);
    return *this;
}

CMatrix CMatrix::operator*(const CMatrix& other) const noexcept
{
    CMatrix result;
    result._matrix = _matrix * other._matrix;
    return result;
}

const float* CMatrix::GetAddress() const noexcept
{
    return &_matrix[0][0];
}
