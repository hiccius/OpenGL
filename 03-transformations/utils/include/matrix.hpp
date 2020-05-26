#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <glm/glm.hpp>

enum class Axis
{
    X, Y, Z
};

class CMatrix
{
public:
    CMatrix() noexcept;

    void Translate(float aX, float aY, float aZ) noexcept;
    void Rotate(float aAngle, Axis aRotationAxis, bool aDegrees=false) noexcept;
    void Scale(float aX, float aY, float aZ) noexcept;

    const float* GetAddress() const noexcept;

private:
    glm::vec3 GetUnitVector(Axis aAxis) const noexcept;

    glm::mat4 _matrix;
};

#endif // TRANSFORMATIONMATRIX_HPP
